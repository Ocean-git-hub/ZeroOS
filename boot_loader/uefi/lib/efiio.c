#include <efiio.h>

#include <stdarg.h>
#include <efistring.h>
#include <efisystab.h>
#include <efiutils.h>

EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;

void efi_io_initialize() {
    ConIn = get_system_table()->ConIn;
    ConOut = get_system_table()->ConOut;
}

void efi_puts(CHAR16 *str) {
    ConOut->EFI_OUT_PUT_STRING(ConOut, str);
}

void efi_putsn(CHAR16 *str) {
    efi_puts(str);
    efi_puts(L"\r\n");
}

void efi_putc(CHAR16 c) {
    CHAR16 buf[2] = {c};
    efi_puts(buf);
}

int efi_printf(const CHAR16 *format, ...) {
    CHAR16 buf[1024];
    va_list args;
    va_start(args, format);
    int len = efi_vsprintf(buf, format, args);
    va_end(args);
    efi_puts(buf);
    return len;
}

EFI_INPUT_KEY efi_get_input_key() {
    EFI_INPUT_KEY key;
    uint64_t index;
    get_system_table()->BootServices->EFI_WAIT_FOR_EVENT(1, &(ConIn->WaitForKey), &index);
    while (ConIn->EFI_INPUT_READ_KEY(ConIn, &key));
    return key;
}

uint64_t efi_gets(CHAR16 *buf, uint64_t buf_size) {
    uint64_t i;
    for (i = 0; i < buf_size - 1;) {
        buf[i] = efi_get_input_key().UnicodeChar;
        efi_putc(buf[i]);
        if (buf[i] == L'\r' || buf[i] == L'\n') {
            efi_putsn(L"");
            break;
        }
        i++;
    }
    buf[i] = L'\0';

    return i;
}

void efi_clear_screen() {
    ConOut->EFI_TEXT_CLEAR_SCREEN(ConOut);
}

void efi_set_largest_screen_mode() {
    ConOut->EFI_TEXT_SET_MODE(ConOut, get_largest_screen_mode());
}
