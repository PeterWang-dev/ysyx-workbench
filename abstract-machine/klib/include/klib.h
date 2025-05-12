/*******************************************************************************
 * Copyright (c) 2018-2021 Yanyan Jiang and Zihao Yu
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
#ifndef KLIB_H__
#define KLIB_H__

#include <am.h>
#include <stdarg.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __NATIVE_USE_KLIB__

// string.h
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
char *strcat(char *dst, const char *src);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

// stdlib.h
void srand(unsigned int seed);
int rand(void);
void *malloc(size_t size);
void free(void *ptr);
int abs(int x);
int atoi(const char *nptr);
char* itoa(int value, char *str);

// stdio.h
int printf(const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);

// assert.h
#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(cond)                                                           \
  do {                                                                         \
    if (!(cond)) {                                                             \
      printf("Assertion fail at %s:%d\n", __FILE__, __LINE__);                 \
      halt(1);                                                                 \
    }                                                                          \
  } while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif
