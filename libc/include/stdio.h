#ifndef ZEROOS_STDIO_H
#define ZEROOS_STDIO_H

#include <stdarg.h>

int vsprintf(char *s, const char *format, va_list arg);

int sprintf(char *str, const char *format, ...);

int printf(const char *format, ...) __attribute__((weak));

#endif //ZEROOS_STDIO_H
