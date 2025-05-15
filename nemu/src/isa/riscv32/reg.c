/*******************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *               2023-2024 PeterWang-dev (https://github.com/PeterWang-dev)
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

#include "local-include/reg.h"
#include "macro.h"
#include <isa.h>

const char *regs[] = {"$0", "ra", "sp",  "gp",  "tp", "t0", "t1", "t2",
                      "s0", "s1", "a0",  "a1",  "a2", "a3", "a4", "a5",
                      "a6", "a7", "s2",  "s3",  "s4", "s5", "s6", "s7",
                      "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"};

void isa_reg_display() {
  for (int i = 0; i < MUXDEF(CONFIG_RVE, 16, 32); i++) {
    printf("%s\t0x%x\n", regs[i], cpu.gpr[i]);
  }
  printf("mstatus\t0x%x\n", cpu.csr[MSTATUS]);
  printf("mtvec\t0x%x\n", cpu.csr[MTVEC]);
  printf("mepc\t0x%x\n", cpu.csr[MEPC]);
  printf("mcause\t0x%x\n", cpu.csr[MCAUSE]);
}

word_t isa_reg_str2val(const char *s, bool *success) {
  if (strcmp(s, "pc") == 0) {
    *success = true;
    return cpu.pc;
  }

  // zero register ('$' is omitted when tokenizing in sdb expr)
  if (strcmp(s, "0") == 0) {
    *success = true;
    return cpu.gpr[0];
  }

  int i;
  for (i = 1; i < 32; i++) { // general purpose registers
    if (strcmp(s, regs[i]) == 0) {
      *success = true;
      return gpr(i);
    }
  }

  *success = false; // if register not found
  return 0;
}
