#ifndef ZEROOS_KERNEL_H
#define ZEROOS_KERNEL_H

#include <stdint.h>

#define structure_check_pointer_member(pointer, type, member) \
    ({typeof(((type *)0)->member) * _ = (pointer);})

#define structure_container_of(pointer, type, member) \
    ({structure_check_pointer_member(pointer, type, member); \
      (type *)((char *)(pointer) - offsetof(type, member));})

typedef struct {
    uintptr_t kernelStart;
    uintptr_t kernelSize;
} KernelInfo;

#endif //ZEROOS_KERNEL_H
