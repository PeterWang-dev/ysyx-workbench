#include <am.h>
#include <klib-macros.h>
#include <klib.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *format, ...) { panic("Not implemented"); }

int sprintf(char *str, const char *format, ...) {
  int cnt = 0;
  va_list ap;

  va_start(ap, format);

  for (const char *ch = format; *ch != '\0'; ch++) {
    switch (*ch) {
    case '%': { // format specifier
      ch++;
      switch (*ch) {
      case 'd': {
        int num = va_arg(ap, int);
        char *start = str, *end = itoa(num, str);
        cnt += end - start;
        str = end;
        break;
      }
      case 's': {
        const char *s = va_arg(ap, const char *);
        while (*s != '\0') {
          *str++ = *s++;
          cnt++;
        }
        break;
      }
      default: {
        panic("Not implemented");
      }
      }
      break;
    }

    default: { // normal characters
      *str++ = *ch;
      cnt++;
    }
    }
  }
  *str = '\0'; // null-terminator on the end of output

  va_end(ap);

  return cnt;
}

int snprintf(char *str, size_t size, const char *format, ...) {
  panic("Not implemented");
}

int vsprintf(char *str, const char *format, va_list ap) {
  panic("Not implemented");
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  panic("Not implemented");
}

#endif
