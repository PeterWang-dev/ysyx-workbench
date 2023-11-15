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
    {"\\*", '*'},                  // multiply
    {"\\\\", '\\'},                // divide
    {"\\+", '+'},                  // plus
    {"-", '-'},                    // minus
    {"==", TK_EQ},                 // equal
    {"[[:digit:]]+", TK_NUM},      // decimal number
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

        if (rules[i].token_type != TK_NOTYPE)
          tokens[nr_token].type = rules[i].token_type;

        switch (rules[i].token_type) {
        case TK_NUM:
          if (substr_len > 32) {
            printf("number %s is too long", substr_start);
            return false;
          }

          char *ch;
          int pch = 0;
          for (ch = substr_start; ch < substr_start + substr_len; ch++) {
            tokens[nr_token].str[pch++] = *ch;
          }
          tokens[nr_token].str[pch] = '\0';

        default:
          break;
        }

        Log("generated token %d: type: %d, contents: %s", nr_token,
            tokens[nr_token].type, tokens[nr_token].str);

        nr_token++;

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
  for (int i = 0; i < nr_token; i++) {
    Log("token[%d]: type: %d, content:%s", i, tokens[i].type, tokens[i].str);
  }
  
  return true;
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  TODO();

  return 0;
}
