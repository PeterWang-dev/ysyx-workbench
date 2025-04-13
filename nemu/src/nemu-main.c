/*******************************************************************************
 * Copyright (c) 2014-2022 Yanyan Jiang and Zihao Yu
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

#include "monitor/sdb/sdb.h"
#include <common.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int test_expr(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "error: missing input file path\n");
    return -1;
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "error: cannot open file %s\n", argv[1]);
    return -1;
  }

  uint32_t answer;
  char e[65535];
  while (fscanf(fp, "%u %s", &answer, e) != EOF) {
    bool status = false;
    word_t result = expr(e, &status);

    if (answer != result) {
      panic(
          "test failed: answer %u is not equal to result %u when evaluating %s",
          answer, result, e);
    }
  }

  printf("success!\n");
  return 0;
}

int main(int argc, char *argv[]) {
#ifdef CONFIG_TEST_EXPR
  void init_sdb();
  init_sdb();
  /* Test expr() */
  int ret;
  ret = test_expr(argc, argv);
  return ret;
#endif

  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}
