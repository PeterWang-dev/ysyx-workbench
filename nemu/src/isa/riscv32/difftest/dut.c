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

#include "../local-include/reg.h"
#include <cpu/difftest.h>
#include <isa.h>

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  for (int i = 0; i < MUXDEF(CONFIG_RVE, 16, 32); i++) {
    if (gpr(i) != ref_r->gpr[i]) {
      Log("Mismatch at gpr[%d]: DUT = " FMT_WORD ", REF = " FMT_WORD, i,
      gpr(i),
          ref_r->gpr[i]);
      return false;
    }
  }

  if (cpu.csr[MTVEC] != ref_r->csr[MTVEC]) {
    Log("Mismatch at csr[MTVEC]: DUT = " FMT_WORD ", REF = " FMT_WORD,
        cpu.csr[MTVEC], ref_r->csr[MTVEC]);
    return false;
  }

  if (cpu.csr[MEPC] != ref_r->csr[MEPC]) {
    Log("Mismatch at csr[MEPC]: DUT = " FMT_WORD ", REF = " FMT_WORD,
        cpu.csr[MEPC], ref_r->csr[MEPC]);
    return false;
  }

  if (cpu.csr[MCAUSE] != ref_r->csr[MCAUSE]) {
    Log("Mismatch at csr[MCAUSE]: DUT = " FMT_WORD ", REF = " FMT_WORD,
        cpu.csr[MCAUSE], ref_r->csr[MCAUSE]);
    return false;
  }

  if (cpu.csr[MSTATUS] != ref_r->csr[MSTATUS]) {
    Log("Mismatch at csr[MSTATUS]: DUT = " FMT_WORD ", REF = " FMT_WORD,
        cpu.csr[MSTATUS], ref_r->csr[MSTATUS]);
    return false;
  }

  if (cpu.pc != ref_r->pc) {
    Log("Mismatch at pc: DUT = " FMT_WORD ", REF = " FMT_WORD, cpu.pc,
        ref_r->pc);
    return false;
  }

  return true;
}

void isa_difftest_attach() {}
