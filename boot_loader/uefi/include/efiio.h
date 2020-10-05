#ifndef ZEROOS_EFIIO_H
#define ZEROOS_EFIIO_H

#include <efi/efi.h>

void efi_io_initialize();

void efi_puts(CHAR16 *str);

void efi_putsn(CHAR16 *str);

void efi_putc(CHAR16 c);

int efi_printf(const CHAR16 *format, ...);

EFI_INPUT_KEY efi_get_input_key();

uint64_t efi_gets(CHAR16 *buf, uint64_t buf_size);

void efi_clear_screen();

void efi_set_largest_screen_mode();

#endif //ZEROOS_EFIIO_H
