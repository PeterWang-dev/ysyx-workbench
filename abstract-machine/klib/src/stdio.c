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

int printf(const char *format, ...) {
  char buf[256];

  va_list ap;
  va_start(ap, format);
  int ret = vsprintf(buf, format, ap);
  va_end(ap);

  for (char *ch = buf; *ch != '\0'; ch++) {
    putch(*ch);
  }

  return ret;
}

int sprintf(char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int ret = vsprintf(str, format, ap);
  va_end(ap);
  return ret;
}

int snprintf(char *str, size_t size, const char *format, ...) {
  panic("Not implemented");
}

int vsprintf(char *str, const char *format, va_list ap) {
  int cnt = 0;
  for (const char *ch = format; *ch != '\0'; ch++) {
    switch (*ch) {
    case '%':
      ch++;
      switch (*ch) { // different format specifiers
      case 'd': {
        int num = va_arg(ap, int);
        char *start = str, *end = itoa(num, str);
        cnt += end - start;
        str = end;
        ch++;
        break;
      }

      case 'c': {
        char c = (char)va_arg(ap, int);
        *str++ = c;
        cnt++;
        ch++;
        break;
      }

      case 's': {
        const char *s = va_arg(ap, const char *);
        while (*s != '\0') {
          *str++ = *s++;
          cnt++;
        }
        ch++;
        break;
      }

      default: {
        // panic("Not implemented");
      }
      }
    default: // normal characters
      *str++ = *ch;
      cnt++;
      break;
    }
  }
  *str = '\0'; // null-terminator on the end of output
  return cnt;
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap) {
  panic("Not implemented");
}

#endif
