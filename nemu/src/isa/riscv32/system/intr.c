/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 *PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 *KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 *NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ***************************************************************************************/

#include <isa.h>

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  //! Set MSTATUS to 0x1800 because we are not using it but need to pass
  //! difftest with Spike, so keep it consistent with Spike.
  cpu.csr[MSTATUS] = 0x1800;
  cpu.csr[MEPC] = epc;
  cpu.csr[MCAUSE] = NO;
  IFDEF(CONFIG_ETRACE, log_write("[etrace] exception triggerd at " FMT_PADDR
                                 " because " FMT_WORD "\n",
                                 epc, NO));
  return cpu.csr[MTVEC];
}

word_t isa_query_intr() { return INTR_EMPTY; }
