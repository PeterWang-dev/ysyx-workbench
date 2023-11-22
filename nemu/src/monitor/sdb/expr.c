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
#include <errno.h>
#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <stddef.h>

enum {
  TK_NOTYPE = 256,
  TK_PARENTHESES_LEFT,
  TK_PARENTHESES_RIGHT,
  TK_NUM,
  TK_NEGTIVE,
  TK_EQ,
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {
    {" +", TK_NOTYPE},             // spaces
    {"\\(", TK_PARENTHESES_LEFT},  // left parenthese
    {"\\)", TK_PARENTHESES_RIGHT}, // right parenthese
    {"[[:digit:]]+", TK_NUM},      // unsigned decimal number
    {"\\*", '*'},                  // multiply
    {"\\/", '/'},                  // divide
    {"\\+", '+'},                  // plus
    {"-", '-'},                    // minus
    {"==", TK_EQ},                 // equal
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

static bool trim_tokenize(char *expr) {
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

        switch (rules[i].token_type) {
        case TK_NUM:
          if (substr_len >= 32) {
            printf("number %s is out of range\n", substr_start);
            return false;
          }

          char *ch;
          int pch = 0;
          for (ch = substr_start; ch < substr_start + substr_len; ch++) {
            tokens[cur_pos].str[pch++] = *ch;
          }
          tokens[cur_pos].str[pch] = '\0'; // terminate raw string of a number

        default:
          break;
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

static bool is_negtive(int pos) {
  if (tokens[pos].type == '-') {
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

static void detect_negtive() {
  int i;
  for (i = 0; i < nr_token; i++) {
    if (is_negtive(i)) {
      tokens[i].type = TK_NEGTIVE;
    }
  }
}

static bool make_token(char *e) {
  int i;

  if (!trim_tokenize(e)) {
    // error has been printed in trim_tokenize
    return false;
  }

  detect_negtive();

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
    if (tokens[i].type == TK_NUM ||
        tokens[i].type == TK_NEGTIVE) { // TK_NUM and TK_NEGTIVE is not operator
      continue;
    }

    /* Rule 2: operators in parentheses are not main_ops */
    if (tokens[i].type == TK_PARENTHESES_LEFT) {
      valid_cnt++;
      continue;
    } else if (tokens[i].type == TK_PARENTHESES_RIGHT) {
      valid_cnt--;
      continue; // Rule 1: parentheses should be skipped too
    }

    /* Rule 3: main_op is the last operation to be evaluate */
    /*         (obeys arithmatic rules and left associative rule) */
    if (valid_cnt == 0) {
      switch (main_op) {
      case -1:
      case '*':
      case '/':
        // left associative and highest order make main_op always be updated
        op_index = i;
        main_op = tokens[i].type;
        break;
      case '+':
      case '-':
        // only update in same level when current main_op is lowest order
        if (tokens[i].type == '+' || tokens[i].type == '-') {
          op_index = i;
          main_op = tokens[i].type;
        }
        break;
      default:
        panic("should not reach here");
        break;
      }
    }
  }

  return op_index;
}

/* Unwrap both positive and negtive number. */
static long unwarp_num(int sp, int ep, bool *success) {
  Assert(tokens[ep].type == TK_NUM && *(tokens[ep].str) != '\0',
         "str in TK_NUM should not be empty");

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
    printf("number %ld out of range\n", number);
    *success = false;
    return 0;
  }

  long result = is_neg ? -number : number;

  *success = true;
  return result;
}

static long eval(int sp, int ep, bool *success) {
  if (sp > ep) { // such as no expr in parentheses
    printf("invalid expression\n");
    *success = false;
    return 0;
  }

  if (ep - sp < 2) { // TK_NEGTIVE or TK_NUM
    return unwarp_num(sp, ep, success);
  }

  if (check_parentheses(sp, ep) == true) { // TK_PARENTHESES
    return eval(sp + 1, ep - 1, success);
  }

  /* normal evaluation */
  long result = 0;

  // find main operator
  int mop_pos = find_op(sp, ep);
  if (mop_pos < 0) {
    printf("invalid expression\n");
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
  case '+':
    result = lres + rres;
    break;
  case '-':
    result = lres - rres;
    break;
  case '*':
    result = lres * rres; // overflow may occur in multiplication
    break;
  case '/':
    if (rres == 0) {
      printf("arithmatic error: divided by 0\n");
      *success = false;
      return 0;
    }
    result = lres / rres;
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
