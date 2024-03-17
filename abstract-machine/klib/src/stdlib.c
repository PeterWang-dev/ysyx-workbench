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

int itoa(const int value, char *str) {
  char buffer[10]; // only handle int
  char *p = buffer; // always points to the (last digit + 1)
  int val = value;
  int cnt = 0;

  // special cases: zero and negative numbers
  if (value == 0) { //! BUG OCCURS HERE
    *p++ = '0';
    cnt = 1;
  } else if (value < 0) {
    val = -value;
    *p++ = '-';
    cnt++;
  }

  // modulo 10 to get the digit stack
  while (val != 0) {
    *p++ = val % 10 + '0';
    val /= 10;
  }

  // reverse output
  while (p != buffer) {
    *str = *--p;
    str++;
    cnt++;
  }
  *str = '\0'; // null-terminator

  // return the length of the string, excluding the null-terminator
  return cnt;
}

void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic()
#if !(defined(__ISA_NATIVE__) && defined(__NATIVE_USE_KLIB__))
  panic("Not implemented");
#endif
  return NULL;
}

void free(void *ptr) {}

#endif
