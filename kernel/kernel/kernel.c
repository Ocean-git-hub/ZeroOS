#include <zero/kernel.h>
#include <zero/tty.h>
#include <zero/vram.h>
#include <zero/physicalmm.h>

typedef struct {
    FrameBufferInfo frameBufferInfo;
    EFIMemoryMap efiMemoryMap;
    KernelInfo kernelInfo;
} BootParameter;

void kernel_main(BootParameter *boot_parameter) {
    vram_initialize(&boot_parameter->frameBufferInfo);
    terminal_initialize();
    physical_mm_initialize(&boot_parameter->efiMemoryMap, &boot_parameter->kernelInfo);
    kprintf("Hello\n");
}
