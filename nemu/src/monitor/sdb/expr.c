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
#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256,
  TK_PARENTHESES_LEFT,
  TK_PARENTHESES_RIGHT,
  TK_NUM,
  TK_EQ,
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {
    {" +", TK_NOTYPE},             // spaces
    {"\\(", TK_PARENTHESES_LEFT},  // left parenthese
    {"\\)", TK_PARENTHESES_RIGHT}, // right parenthese
    {"-?[[:digit:]]+", TK_NUM},    // decimal number
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

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 &&
          pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i,
            rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        int ptoken = nr_token;

        switch (rules[i].token_type) {
        case TK_NUM:
          if (substr_len > 32) {
            printf("number %s is too long", substr_start);
            return false;
          }

          char *ch;
          int pch = 0;
          for (ch = substr_start; ch < substr_start + substr_len; ch++) {
            tokens[ptoken].str[pch++] = *ch;
          }
          tokens[ptoken].str[pch] = '\0'; // terminate raw string of a number

        default:
          break;
        }

        if (rules[i].token_type != TK_NOTYPE) {
          tokens[ptoken].type = rules[i].token_type;
          nr_token++;

          Log("generated token %d: type: %d, contents: %s", nr_token,
              tokens[ptoken].type, tokens[ptoken].str);
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

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

  int i;
  int leftpar_remains = 0;
  for (i = sp + 1; i < ep; i++) {
    if (tokens[i].type == TK_PARENTHESES_LEFT) {
      leftpar_remains++;
    } else if (tokens[i].type == TK_PARENTHESES_RIGHT) {
      leftpar_remains--;
    }
  }

  return leftpar_remains == 0; // left means internal parentheses are not closed
}

static int find_op(int sp, int ep) {
  Assert(sp <= ep, "start pos %d should smaller or equal than %d", sp, ep);

  bool is_valid = true; // marker to demostrate if in paretheses
  int main_op = -1;     // lowest level (last) operator
  int op_index = -1;    // index of lowest level (last) operator

  int i;
  for (i = sp; i <= ep; i++) {
    Assert(tokens[i].type != TK_NOTYPE,
           "spaces should not exists after making token");

    /* Rule 1: elems which is not an operator is definately not a main_op */
    if (tokens[i].type == TK_NUM) { // TK_NUM is not operator
      continue;
    }

    /* Rule 2: operators in parentheses are not main_ops */
    if (tokens[i].type == TK_PARENTHESES_LEFT) {
      is_valid = false;
      continue;
    } else if (tokens[i].type == TK_PARENTHESES_RIGHT) {
      is_valid = true;
      continue; // Rule 1: parentheses should be skipped too
    }

    /* Rule 3: main_op is the last operation to be evaluate */
    /*         (obeys arithmatic rules and left associative rule) */
    if (is_valid) {
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
        Assert(0, "should not reach here");
        break;
      }
    }
  }

  return op_index;
}

static sword_t eval(int sp, int ep, bool *success) {
  /* special cases */
  if (sp > ep) { // such as no expr in parentheses
    printf("invalid expression\n");
    *success = false;
    return 0;
  } else if (sp == ep) { // TK_NUM
    Assert(*tokens[sp].str != '\0',
           "contents in TK_NUM token should not be empty");

    char *str = tokens[sp].str;
    char *endptr = str;

    sword_t number = strtol(str, &endptr, 10);

    if (*endptr == '\0') {
      *success = true;
      return number;
    } else {
      printf("str %s number conversion failed!", str);
      *success = false;
      return 0;
    }
  } else if (check_parentheses(sp, ep) == true) { // TK_PARENTHESES
    return eval(sp + 1, ep - 1, success);
  }

  /* normal evaluation */
  sword_t res = 0;

  // find main operator
  int mop_pos = find_op(sp, ep);
  if (mop_pos < 0) {
    printf("invalid expression\n");
    *success = false;
    return 0;
  }

  // recursive evaluate
  bool lstat = false;
  sword_t lres = eval(sp, mop_pos - 1, &lstat);
  bool rstat = false;
  sword_t rres = eval(mop_pos + 1, ep, &rstat);
  if (!(lstat && rstat)) {
    *success = false;
    return 0;
  }

  // arithmatic evaluate
  switch (tokens[mop_pos].type) {
  case '+':
    res = lres + rres;
    break;
  case '-':
    res = lres - rres;
    break;
  case '*':
    res = lres * rres;
    break;
  case '/':
    res = lres / rres;
    break;
  default:
    Assert(0, "should not reach here");
    break;
  }

  *success = true;
  return res;
}

sword_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  sword_t res = eval(0, nr_token - 1, success);

  return res;
}
