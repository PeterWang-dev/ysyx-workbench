/*******************************************************************************
 * Copyright (c) 2023-2024 PeterWang-dev (https://github.com/PeterWang-dev)
 *
 * AbstractMachine is licensed under Mulan PSL v2.
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
#include <am.h>
#include <klib-macros.h>
#include <klib.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed) { next = seed; }

int abs(int x) { return (x < 0 ? -x : x); }

int atoi(const char *nptr) {
  int x = 0;
  while (*nptr == ' ') {
    nptr++;
  }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr++;
  }
  return x;
}

char *ltoa(long value, char *string, int radix) {
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v;
  int sign;
  char *sp;

  if (string == NULL) {
    return 0;
  }

  if (radix > 36 || radix <= 1) {
    return 0;
  }

  sign = (radix == 10 && value < 0);
  if (sign) {
    v = -value;
  } else {
    v = (unsigned long)value;
  }

  while (v || tp == tmp) {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = (char)(i + '0');
    else
      *tp++ = (char)(i + 'a' - 10);
  }

  sp = string;

  if (sign)
    *sp++ = '-';
  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}

char *itoa(int value, char *string, int radix) {
  return ltoa(value, string, radix);
}

char *ultoa(unsigned long value, char *string, int radix) {
  char tmp[33];
  char *tp = tmp;
  long i;
  unsigned long v = value;
  char *sp;

  if (string == NULL) {
    return 0;
  }

  if (radix > 36 || radix <= 1) {
    return 0;
  }

  while (v || tp == tmp) {
    i = v % radix;
    v = v / radix;
    if (i < 10)
      *tp++ = (char)(i + '0');
    else
      *tp++ = (char)(i + 'a' - 10);
  }

  sp = string;

  while (tp > tmp)
    *sp++ = *--tp;
  *sp = 0;

  return string;
}

char *utoa(unsigned value, char *string, int radix) {
  return ultoa(value, string, radix);
}

void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
  // #if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  //   panic("Not implemented");
  // #endif
  static char *addr = NULL; // static variable, keep track of the heap
  if (addr == NULL) {       // first time malloc() is called
    addr = heap.start;
  }
  void *ptr = addr;
  addr += size;
  return ptr;
}

void free(void *ptr) {}

#endif
