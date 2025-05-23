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
#include <klib-macros.h>
#include <klib.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static void *mempcpy(void *dest, const void *src, size_t n) {
  unsigned char *cdest = (unsigned char *)dest;
  const unsigned char *csrc = (unsigned char *)src;

  size_t i;
  for (i = 0; i < n; i++) {
    cdest[i] = csrc[i];
  }

  return (void *)(cdest + n);
}

void *memcpy(void *dest, const void *src, size_t n) {
  mempcpy(dest, src, n);
  return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
  unsigned char tmp[n]; // C99 VLA

  memcpy(tmp, src, n);
  memcpy(dest, tmp, n);

  free(tmp);

  return dest;
}

void *memset(void *s, int c, size_t n) {
  unsigned char *cs = (unsigned char *)s;

  size_t i;
  for (i = 0; i < n; i++) {
    cs[i] = c;
  }

  return s;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *cs1 = (const unsigned char *)s1;
  const unsigned char *cs2 = (const unsigned char *)s2;

  size_t i;
  for (i = 0; i < n; i++) {
    if (cs1[i] != cs2[i]) {
      return cs1[i] - cs2[i];
    }
  }

  return 0;
}

size_t strlen(const char *s) {
  size_t len = 0;

  for (; *s != '\0'; s++) {
    len++;
  }

  return len;
}

static size_t strnlen(const char *s, size_t maxlen) {
  size_t len = 0;

  for (; s < s + maxlen && s[len] != '\0'; s++) {
    len++;
  }

  return len;
}

char *stpcpy(char *dst, const char *src) {
  char *p;

  p = mempcpy(dst, src, strlen(src));
  *p = '\0';

  return p;
}

char *strcpy(char *dst, const char *src) {
  stpcpy(dst, src);
  return dst;
}

char *strcat(char *dst, const char *src) {
  stpcpy(dst + strlen(dst), src);
  return dst;
}

static char *stpncpy(char *dst, const char *src, size_t dsize) {
  size_t dlen;

  dlen = strnlen(src, dsize);
  // BUG: Segmentation fault occurs here.
  return memset(mempcpy(dst, src, dlen), 0, dsize - dlen);
}

char *strncpy(char *dst, const char *src, size_t dsize) {
  stpncpy(dst, src, dsize);
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  const unsigned char *us1 = (const unsigned char *)s1;
  const unsigned char *us2 = (const unsigned char *)s2;

  for (; *us1 != '\0' && *us2 != '\0'; us1++, us2++) {
    if (*us1 != *us2) {
      return *us1 - *us2;
    }
  }

  return *us1 - *us2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  const unsigned char *us1 = (const unsigned char *)s1;
  const unsigned char *us2 = (const unsigned char *)s2;

  for (size_t i = 0; i < n; i++) {
    if (us1[i] != us2[i]) {
      return us1[i] - us2[i];
    }
  }

  return 0;
}

#endif
