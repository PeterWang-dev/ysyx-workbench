#ifndef NPC_H__
#define NPC_H__

#include <klib-macros.h>
#include "riscv/riscv.h"

#define npc_trap(code) asm volatile("mv a0, %0; ebreak" : : "r"(code))

#define DEVICE_BASE 0xa0000000

#define SERIAL_PORT (DEVICE_BASE + 0x00003f8)
#define RTC_ADDR (DEVICE_BASE + 0x0000048)

#endif