#ifndef ZEROOS_EFI_STRING_H
#define ZEROOS_EFI_STRING_H

#include <stddef.h>
#include <efi/efi.h>

CHAR16 *efi_strcat(CHAR16 *s1, const CHAR16 *s2);

size_t efi_strlen(const CHAR16 *s);

CHAR16 *efi_strncpy(CHAR16 *s1, const CHAR16 *s2, size_t n);

CHAR16 *efi_strcpy(CHAR16 *s1, const CHAR16 *s2);

int efi_strcmp(const CHAR16 *s1, const CHAR16 *s2);

int64_t find_string_r(CHAR16 *str, CHAR16 *token);

int efi_vsprintf(CHAR16 *s, const CHAR16 *format, va_list args);

#endif //ZEROOS_EFI_STRING_H
