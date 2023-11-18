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

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format = "#include <stdio.h>\n"
                           "int main() { "
                           "  unsigned result = %s; "
                           "  printf(\"%%u\", result); "
                           "  return 0; "
                           "}";

static int buf_pos = 0;

/*
 * Generate a random number in range [0, n)
 */
static uint32_t choose(uint32_t n) {
  srand(time(NULL));
  int r = rand();
  return r % n;
}

static void gen(char ch) { buf[buf_pos++] = ch; }

static void gen_num() {
  uint32_t random = choose(UINT32_MAX);
  char num_str[11] = ""; // max length of 32-bit decimal is 10 + 1 for '\0'
  sprintf(num_str, "%u", random);

  char *pstr;
  for (pstr = num_str; pstr < num_str + strlen(num_str); pstr++) {
    gen(*pstr);
  }
}

static void gen_rand_op() {
  uint32_t op_sel = choose(4);
  switch (op_sel) {
  case 0:
    gen('+');
  case 1:
    gen('-');
  case 2:
    gen('*');
  case 3:
    gen('/');
  default:
    fprintf(stderr, "should not reach here\n");
    assert(0);
  }
}

static void reset_gen() {
  buf_pos = 0;
  buf[buf_pos] = '\0';
}

static void gen_rand_expr() {
  switch (choose(3)) {
  case 0: //
    gen_num();
    break;
  case 1:
    gen('(');
    gen_rand_expr();
    gen(')');
    break;
  case 2:
    gen_rand_expr();
    gen_rand_op();
    gen_rand_expr();
    break;
  default:
    fprintf(stderr, "should not reach here");
    assert(0);
  }
  buf[buf_pos] = '\0';
}

int main(int argc, char *argv[]) {
  time_t seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i++) {
    reset_gen();
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0)
      continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
