#ifndef ZEROOS_STRING_H
#define ZEROOS_STRING_H

#include <stddef.h>
#include <stdarg.h>

size_t strlen(const char *s);

char *strcat(char *s1, const char *s2);

char *strcpy(char *s1, const char *s2);

char *strncpy(char *s1, const char *s2, size_t n);

int strcmp(const char *s1, const char *s2);

int vsprintf(char *s, const char *format, va_list arg);

int sprintf(char *str, const char *format, ...);

#endif //ZEROOS_STRING_H
