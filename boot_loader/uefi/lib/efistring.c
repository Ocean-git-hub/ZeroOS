#include <efistring.h>
#include <stdarg.h>
#include <efi/efi.h>

#define _MAX_DECIMAL_BUFFER 20
#define _READING_ZERO_BUFFER_SIZE 3

CHAR16 *efi_strcat(CHAR16 *s1, const CHAR16 *s2) {
    CHAR16 *const _s1 = s1;
    for (; *s1; s1++);
    while (*s2)
        *s1++ = *s2++;
    *s1 = 0;
    return _s1;
}

size_t efi_strlen(const CHAR16 *s) {
    size_t len;
    for (len = 0; *s++; len++);
    return len;
}

CHAR16 *efi_strncpy(CHAR16 *s1, const CHAR16 *s2, size_t n) {
    CHAR16 *const _s1 = s1;
    for (; n && *s2; n--)
        *s1++ = *s2++;
    while (n--)
        *s1++ = 0;
    return _s1;
}

CHAR16 *efi_strcpy(CHAR16 *s1, const CHAR16 *s2) {
    CHAR16 *const _s1 = s1;
    while (*s2)
        *s1++ = *s2++;
    *s1 = 0;
    return _s1;
}

int efi_strcmp(const CHAR16 *s1, const CHAR16 *s2) {
    for (; *s1 == *s2 && *s1; s1++, s2++);
    return *s1 - *s2;
}

int64_t find_string_r(CHAR16 *str, CHAR16 *token) {
    const int64_t token_len = efi_strlen(token);
    int64_t token_index = token_len;
    for (int64_t i = efi_strlen(str) - 1; i >= 0; i--) {
        if (str[i] != token[--token_index])
            token_index = token_len;
        if (token_index == 0)
            return i;
    }
    return -1;
}

uint8_t efi_s_print_unsigned_decimal(uint64_t value, CHAR16 *s) {
    uint8_t digit = 1;
    uint64_t value_tmp = value;
    while ((value_tmp /= 10) != 0)
        digit++;
    s[digit] = 0;
    for (int16_t i = digit - 1; i >= 0; i--) {
        s[i] = L'0' + value % 10;
        value /= 10;
    }
    return digit;
}

uint8_t efi_s_print_decimal(uint64_t value, CHAR16 *s) {
    CHAR16 is_signed = value >> 63U;
    if (is_signed) {
        *s++ = L'-';
        value *= -1;
    }
    return efi_s_print_unsigned_decimal(value, s) + is_signed;
}

int8_t efi_s_print_hex64(uint64_t value, CHAR16 *s) {
    CHAR16 tmp[17] = {0}, unit_val;
    int8_t i;
    uint8_t j = 0;
    for (i = 0; i < 16 && value > 0; i++) {
        unit_val = value & 0xfU;
        tmp[i] = unit_val + ((unit_val < 0xa) ? L'0' : L'A' - 0xa);
        value >>= 4U;
    }
    if (i == 0)
        s[j++] = L'0';
    while (i > 0)
        s[j++] = tmp[--i];
    s[j] = '\0';
    return j;
}

int8_t efi_s_print_hex32(uint32_t value, CHAR16 *s) {
    CHAR16 tmp[9] = {0}, unit_val;
    int8_t i;
    uint8_t j = 0;
    for (i = 0; i < 8 && value > 0; i++) {
        unit_val = value & 0xfU;
        tmp[i] = unit_val + ((unit_val < 0xa) ? L'0' : L'A' - 0xa);
        value >>= 4U;
    }
    if (i == 0)
        s[j++] = L'0';
    while (i > 0)
        s[j++] = tmp[--i];
    s[j] = '\0';
    return j;
}

void efi_s_print_double(double value, CHAR16 *s) {
    uint64_t bits = *(uint64_t *) &value;
    if (bits >> 63U) {
        *s++ = L'-';
        value *= -1;
    }
    uint64_t before_decimal_point = value;
    s += efi_s_print_unsigned_decimal(before_decimal_point, s);
    *s++ = L'.';
    uint64_t after_decimal_point6 = value * 1000000 - before_decimal_point * 1000000 + 1000000;
    efi_s_print_unsigned_decimal(after_decimal_point6, s);
    for (int i = 0; i < 7; ++i)
        s[i] = s[i + 1];
}

int64_t efi_power(uint8_t x, uint8_t y) {
    uint8_t ret_x = 1;
    for (uint8_t i = 0; i < y; ++i)
        ret_x *= x;
    return ret_x;
}

int efi_vsprintf(CHAR16 *s, const CHAR16 *format, va_list args) {
    CHAR16 reading_zero_buf[_READING_ZERO_BUFFER_SIZE] = {0}, buf[_MAX_DECIMAL_BUFFER + 1], *arg_char, *_s = s;
    uint8_t reading_zero_buf_index, reading_zero;
    int8_t n_reading_zero;
    while (*format != '\0') {
        if (*format != L'%') {
            *s++ = *format++;
            continue;
        } else if (format[1] == L'%') {
            *s++ = *format++;
            format++;
            continue;
        }
        format++;
        reading_zero = reading_zero_buf_index = 0;
        if (*format == L'0') {
            format++;
            while (L'0' <= *format && *format <= L'9')
                if (reading_zero_buf_index < _READING_ZERO_BUFFER_SIZE)
                    reading_zero_buf[reading_zero_buf_index++] = *format++;
            for (uint8_t i = 0; i < reading_zero_buf_index; ++i)
                reading_zero += (reading_zero_buf[reading_zero_buf_index - i - 1] - '0') * efi_power(10, i);
        }
        switch (*format) {
            case L'c':
                *s++ = va_arg(args, int32_t);
                break;
            case L's':
                arg_char = va_arg(args, CHAR16*);
                efi_strcpy(s, arg_char);
                s += efi_strlen(arg_char);
                break;
            case L'f':
                efi_s_print_double(va_arg(args, double), buf);
                efi_strcpy(s, buf);
                s += efi_strlen(buf);
                break;
            default:
                switch (*format) {
                    case L'd':
                        n_reading_zero = reading_zero - efi_s_print_decimal(va_arg(args, int32_t), buf);
                        break;
                    case L'u':
                        n_reading_zero = reading_zero - efi_s_print_unsigned_decimal(va_arg(args, int32_t), buf);
                        break;
                    case L'x':
                        n_reading_zero = reading_zero - efi_s_print_hex32(va_arg(args, int32_t), buf);
                        break;
                    case L'l':
                        switch (*++format) {
                            case L'd':
                                n_reading_zero = reading_zero - efi_s_print_decimal(va_arg(args, int64_t), buf);
                                break;
                            case L'u':
                                n_reading_zero =
                                        reading_zero - efi_s_print_unsigned_decimal(va_arg(args, int64_t), buf);
                                break;
                            case L'x':
                                n_reading_zero = reading_zero - efi_s_print_hex64(va_arg(args, int64_t), buf);
                                break;
                            default:
                                *s++ = L'%';
                                *s++ = L'l';
                                *s++ = *format++;
                                continue;
                        }
                        break;
                    default:
                        *s++ = L'%';
                        *s++ = *format++;
                        continue;
                }
                for (int j = 0; j < n_reading_zero; ++j)
                    *s++ = L'0';
                efi_strcpy(s, buf);
                s += efi_strlen(buf);
        }
        format++;
    }
    *s = 0;
    return efi_strlen(_s);
}
