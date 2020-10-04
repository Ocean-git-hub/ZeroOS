#ifndef ZEROOS_STRING_H
#define ZEROOS_STRING_H

#include <efi/efi.h>

void cat_string(CHAR16 *dest, CHAR16 *src);

uint64_t str_len(CHAR16 *str);

void str_n_copy(CHAR16 *dest, CHAR16 *src, int64_t n);

void str_copy(CHAR16 *dest, CHAR16 *src);

int8_t str16_cmp(CHAR16 *s1, CHAR16 *s2);

int8_t str8_cmp(int8_t *s1, int8_t *s2);

int64_t find_string_r(CHAR16 *str, CHAR16 *token);

#endif //ZEROOS_STRING_H
