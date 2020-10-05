#include <string.h>

char *strncpy(char *s1, const char *s2, size_t n) {
    char *const _s1 = s1;
    for (; n && *s2; n--)
        *s1++ = *s2++;
    while (n--)
        *s1++ = 0;
    return _s1;
}
