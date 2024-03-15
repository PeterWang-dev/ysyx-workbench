#include <klib-macros.h>
#include <klib.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static void *mempcpy(void *dest, const void *src, size_t n) {
  unsigned char *cdest = (unsigned char *)dest;
  const unsigned char *csrc = (unsigned char *)src;

  for (size_t i = 0; i < n; i++) {
    cdest[i] = csrc[i];
  }

  return (void *)(cdest + n);
}

void *memcpy(void *dest, const void *src, size_t n) {
  mempcpy(dest, src, n);
  return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
  unsigned char *tmp = (unsigned char *)malloc(n);

  memcpy(tmp, src, n);
  memcpy(dest, tmp, n);

  free(tmp);

  return dest;
}

void *memset(void *s, int c, size_t n) {
  unsigned char *cs = (unsigned char *)s;

  for (size_t i = 0; i < n; i++) {
    cs[i] = c;
  }

  return s;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *cs1 = (const unsigned char *)s1;
  const unsigned char *cs2 = (const unsigned char *)s2;

  for (size_t i = 0; i < n; i++) {
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

char *stpcpy(char * dst, const char * src) {
  char *p;

  p = mempcpy(dst, src, strlen(src));
  *p = '\0';

  return p;
}

char *strcpy(char * dst, const char * src) {
  stpcpy(dst, src);
  return dst;
}

char *strcat(char * dst, const char * src) {
  stpcpy(dst + strlen(dst), src);
  return dst;
}

static char *stpncpy(char * dst, const char * src,
                     size_t dsize) {
  size_t dlen;

  dlen = strnlen(src, dsize);
  return memset(mempcpy(dst, src, dlen), 0, dsize - dlen);
}

char *strncpy(char * dst, const char * src, size_t dsize) {
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
