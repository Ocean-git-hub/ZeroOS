#include <string.h>

char *strcat(char *s1, const char *s2) {
    char *const _s1 = s1;
    for (; *s1; s1++);
    while (*s2)
        *s1++ = *s2++;
    *s1 = 0;
    return _s1;
}
