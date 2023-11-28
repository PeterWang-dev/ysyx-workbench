/*******************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *               2023-2024 PeterWang-dev (https://github.com/PeterWang-dev)
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 *******************************************************************************/

#include "debug.h"
#include "memory/paddr.h"
#include <errno.h>
#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <stddef.h>

enum {
  TK_NOTYPE,
  TK_PARENTHESES_LEFT,
  TK_PARENTHESES_RIGHT,
  TK_REG,
  TK_NUM,
  TK_NEGTIVE,
  TK_DEREF,
  TK_MUL,
  TK_DIV,
  TK_ADD,
  TK_SUB,
  TK_EQ,
  TK_NEQ,
  TK_AND,
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {
    {" +", TK_NOTYPE},                // spaces
    {"\\(", TK_PARENTHESES_LEFT},     // left parenthese
    {"\\)", TK_PARENTHESES_RIGHT},    // right parenthese
    {"\\$.*", TK_REG},                // register
    {"(0[xX])?[0-9A-Ea-e]+", TK_NUM}, // unsigned number
    {"\\*", TK_MUL},                  // multiply
    {"\\/", TK_DIV},                  // divide
    {"\\+", TK_ADD},                  // plus
    {"-", TK_SUB},                    // minus
    {"==", TK_EQ},                    // equal
    {"!=", TK_NEQ},                   // not equal
    {"&&", TK_AND}                    // and
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static bool basic_tokenize(char *expr) {
  int pos = 0; // position of substring waiting for matching
  int i;
  regmatch_t pmatch;
  nr_token = 0;

  while (expr[pos] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++) {
      if (regexec(&re[i], expr + pos, 1, &pmatch, 0) == 0 &&
          pmatch.rm_so == 0) {
        char *substr_start = expr + pos;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i,
            rules[i].regex, pos, substr_len, substr_len, substr_start);

        pos += substr_len; // move

        int cur_pos = nr_token; // current token pos

        if (rules[i].token_type == TK_NUM || rules[i].token_type == TK_REG) {
          if (rules[i].token_type == TK_NUM && substr_len >= 32) {
            printf("number %s is out of range\n", substr_start);
            return false;
          }

          char *ch;
          int pch = 0;
          for (ch = substr_start; ch < substr_start + substr_len; ch++) {
            tokens[cur_pos].str[pch++] = *ch;
          }
          tokens[cur_pos].str[pch] = '\0'; // terminate raw string of a number
        }

        if (rules[i].token_type != TK_NOTYPE) {
          tokens[cur_pos].type = rules[i].token_type;
          nr_token++;

          Log("generated token %d: type: %d, contents: %s", nr_token,
              tokens[cur_pos].type, tokens[cur_pos].str);
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", pos, expr, pos, "");
      return false;
    }
  }

  return true;
}

static bool is_unary(int pos) {
  if (tokens[pos].type == TK_SUB || tokens[pos].type == TK_MUL) {
    /* look ahead method */
    if (pos == nr_token - 1) { // last token is sign is a invalid expression
                               // not to be dealt with here but when evaluating
      return false;
    }

    if (tokens[pos + 1].type == TK_NUM) { // negtive sign always before number
      /* it is the first token then it must be negtive number */
      if (pos == 0)
        return true;

      /* if previous token is right parenthese or number,
       * then it must not be negtive but a minus sign */
      if (tokens[pos - 1].type == TK_PARENTHESES_RIGHT ||
          tokens[pos - 1].type == TK_NUM) {
        // overflow not occured here as "or" is short-circuit evaluation
        return false;
      }

      /* otherwize it is negive number */
      return true;
    }
  }

  return false;
}

static void post_tokenize() {
  int i;
  for (i = 0; i < nr_token; i++) {
    if (is_unary(i)) {
      if (tokens[i].type == TK_SUB) {
        tokens[i].type = TK_NEGTIVE;
      } else if (tokens[i].type == TK_MUL) {
        tokens[i].type = TK_DEREF;
      }
    }
  }
}

static bool make_token(char *e) {
  int i;

  if (!basic_tokenize(e)) {
    // error has been printed in trim_tokenize
    return false;
  }

  post_tokenize();

  Log("tokens are successfully generated");
  Log("printing token info");
  for (i = 0; i < nr_token; i++) {
    Log("token[%d]: type: %d, content:%s", i, tokens[i].type, tokens[i].str);
  }

  return true;
}

static bool check_parentheses(int sp, int ep) {
  if (tokens[sp].type != TK_PARENTHESES_LEFT ||
      tokens[ep].type != TK_PARENTHESES_RIGHT)
    return false;

  int pos = 0; // simulate stack
  int i;
  for (i = sp + 1; i < ep; i++) {
    if (tokens[i].type == TK_PARENTHESES_LEFT) {
      pos++; // left parenthese then push
    } else if (tokens[i].type == TK_PARENTHESES_RIGHT) {
      if (pos == 0) {
        return false; // right parenthese without left parenthese
      } else {
        pos--; // right parenthese then pop
      }
    }
  }

  return (pos == 0); // if pos != 0, then left parenthese without right
}

static int find_op(int sp, int ep) {
  Assert(sp <= ep, "start pos %d should smaller or equal than %d", sp, ep);

  int valid_cnt = 0; // marker to demostrate if in paretheses
  int main_op = -1;  // lowest level (last) operator
  int op_index = -1; // index of lowest level (last) operator

  int i;
  for (i = sp; i <= ep; i++) {
    Assert(tokens[i].type != TK_NOTYPE,
           "spaces should not exists after making token");

    /* Rule 1: elems which is not an operator is definately not a main_op */
    if (tokens[i].type == TK_NUM || tokens[i].type == TK_NEGTIVE) {
      // TK_NUM and TK_NEGTIVE are not operators
      continue;
    }

    /* Rule 2: operators in parentheses are not main_ops */
    if (tokens[i].type == TK_PARENTHESES_LEFT) {
      valid_cnt++;
      continue;
    } else if (tokens[i].type == TK_PARENTHESES_RIGHT) {
      valid_cnt--;
      continue; // parentheses should be skipped too
    }

    /* Rule 3: main_op is the last operation to be evaluate
     *         obeys C operator precedence and associativity */
    if (valid_cnt == 0 && main_op < tokens[i].type) {
      op_index = i;
      main_op = tokens[i].type;
    }
  }

  return op_index;
}

/* Unwrap both positive and negtive number. */
static long unwarp_num(int sp, int ep, bool *success) {
  Assert(tokens[ep].type == TK_NUM && *(tokens[ep].str) != '\0',
         "token type should be TK_NUM and str in TK_NUM should not be empty");

  char *str = tokens[ep].str;
  char *endptr = str;
  bool is_neg = (tokens[sp].type == TK_NEGTIVE);
  errno = 0;

  long number = strtol(str, &endptr, 0);

  /* handling result */
  // invalid number, should not reach here by design using regex
  if (*endptr != '\0') {
    panic("str %s number conversion failed", str);
  }

  // check number range
  if (errno == ERANGE) {
    printf("conversion error: number %ld out of range\n", number);
    *success = false;
    return 0;
  }

  long result = is_neg ? -number : number;

  *success = true;
  return result;
}

static word_t unwrap_reg(int pos, bool *success) {
  Assert(tokens[pos].type == TK_REG && *(tokens[pos].str) != '\0',
         "token type should be TK_REG and str in TK_REG should not be empty");

  char *name = tokens[pos].str;
  word_t val = isa_reg_str2val(name, success);

  if (!(*success)) {
    printf("conversion error: register %s not found\n", name);
    return 0;
  }

  return val;
}

static long eval(int sp, int ep, bool *success) {
  // note: pay attention to the order of the following if statements
  if (sp > ep) { // such as no expr in parentheses
    printf("invalid expression: missing operands\n");
    *success = false;
    return 0;
  }

  if (tokens[sp].type == TK_DEREF) { // TK_DEREF
    word_t addr = eval(sp + 1, ep, success);
    if (!(*success)) {
      printf("arithmatic error: invalid derefence address\n");
      return 0;
    }
    return paddr_read(addr, 4);
  }

  if (ep - sp < 2) { // TK_NEGTIVE, TK_NUM or TK_REG
    if (tokens[sp].type == TK_NEGTIVE || tokens[sp].type == TK_NUM) {
      return unwarp_num(sp, ep, success);
    } else if (tokens[sp].type == TK_REG) {
      return unwrap_reg(sp, success);
    } else { // should not reach here by design as
             // ep - sp < 2 can only be TK_NEGTIVE, TK_NUM or TK_REG
      panic("should not reach here");
    }
  }

  if (check_parentheses(sp, ep) == true) { // TK_PARENTHESES
    return eval(sp + 1, ep - 1, success);
  }

  /* normal evaluation */
  long result = 0;

  // find main operator
  int mop_pos = find_op(sp, ep);
  if (mop_pos < 0) {
    printf("invalid expression: can not find main operator\n");
    *success = false;
    return 0;
  }

  // recursive evaluate
  bool lstat = false;
  long lres = eval(sp, mop_pos - 1, &lstat);
  bool rstat = false;
  long rres = eval(mop_pos + 1, ep, &rstat);
  if (!(lstat && rstat)) {
    *success = false;
    return 0;
  }

  // arithmatic evaluate
  switch (tokens[mop_pos].type) {
  case TK_ADD:
    result = lres + rres;
    break;
  case TK_SUB:
    result = lres - rres;
    break;
  case TK_MUL:
    result = lres * rres; // overflow may occur in multiplication
    break;
  case TK_DIV:
    if (rres == 0) {
      printf("arithmatic error: divided by 0\n");
      *success = false;
      return 0;
    }
    result = lres / rres;
    break;
  case TK_EQ:
    result = lres == rres;
    break;
  case TK_NEQ:
    result = lres != rres;
    break;
  case TK_AND:
    result = lres && rres;
    break;
  default:
    panic("should not reach here");
    break;
  }

  *success = true;
  return result;
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  word_t result = eval(0, nr_token - 1, success);

  return result;
}
