#ifndef ZEROOS_TTY_H
#define ZEROOS_TTY_H

#include <stddef.h>

void terminal_initialize();

void terminal_putc(char c);

void terminal_write(const char *s, size_t size);

void terminal_write_string(const char *s);

void terminal_puts(const char *s);

int printf(const char *format, ...);

#endif //ZEROOS_TTY_H
