#include <am.h>
#include <klib.h>
#include <nemu.h>
#include <stdint.h>

void __am_timer_init() {}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  printf("Addr Ticks (High, Low): %d, %d\n", RTC_ADDR + 4, RTC_ADDR);
  uint64_t lo = inl(RTC_ADDR);
  printf("[AM]\tLow: %d\n", (uint32_t)lo);
  uint64_t hi = (uint64_t)inl(RTC_ADDR + 4) << 32;
  printf("[AM]\tTick High: %d\n", (uint32_t)(hi >> 32));
  uptime->us = hi | lo;
  // uint64_t ticks = (uint64_t)inl(RTC_ADDR + 4) << 32 | inl(RTC_ADDR);
  // uptime->us = ticks;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour = 0;
  rtc->day = 0;
  rtc->month = 0;
  rtc->year = 1900;
}
