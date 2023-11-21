/*******************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
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
 ******************************************************************************/

#include "monitor/sdb/sdb.h"
#include <common.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  /* Test expr() */
  if (argc < 2) {
    panic("missing input file path");
  }

  FILE *fp = fopen(argv[1], "r");
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
  /* Start engine. */
  // engine_start();

  // return is_exit_status_bad();
}
