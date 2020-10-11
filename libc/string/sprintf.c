#include <string.h>

int sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int len = vsprintf(str, format, args);
    va_end(args);
    return len;
}
