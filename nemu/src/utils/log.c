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
 ******************************************************************************/
#include "macro.h"
#include <common.h>

extern uint64_t g_nr_guest_inst;

#ifndef CONFIG_TARGET_AM
FILE *log_fp = NULL;
RingBuf iringbuf;
static int ft_indent = 0;

void init_log(const char *log_file) {
  log_fp = stdout;
  if (log_file != NULL) {
    FILE *fp = fopen(log_file, "w");
    Assert(fp, "Can not open '%s'", log_file);
    log_fp = fp;
  }
  Log("Log is written to %s", log_file ? log_file : "stdout");

  Log("Initializing intruction ring buffer");
  ringbuf_init(&iringbuf);
}

bool log_enable() {
  return MUXDEF(CONFIG_TRACE,
                (g_nr_guest_inst >= CONFIG_TRACE_START) &&
                    (g_nr_guest_inst <= CONFIG_TRACE_END),
                false);
}

void print_logbuf() { // output log ring buffer
  for (char *buf = ringbuf_iter(&iringbuf); buf != NULL;
       buf = ringbuf_iter(&iringbuf)) {
    fprintf(stderr, "%s\n", buf);
  }
}

extern char *find_symbol(vaddr_t addr);
extern bool ftrace_enabled;

void log_ftrace(vaddr_t dnpc, int type) {
  if (!ftrace_enabled) {
    return;
  }

  IFDEF(CONFIG_FTRACE, {
    fprintf(log_fp, "[ftrace]");
    switch (type) {
    case 1:
      ft_indent++;
      fprintf(log_fp, "%*ccall %08x <%s>\n", 2 * ft_indent, ' ', dnpc,
              find_symbol(dnpc));
      break;
    case -1:
      fprintf(log_fp, "%*creturn to %08x <%s>\n", 2 * ft_indent, ' ', dnpc,
              find_symbol(dnpc));
      ft_indent--;
      break;
    default:
      panic("Unknown ftrace type %d", type);
    }
  });
}

#endif
