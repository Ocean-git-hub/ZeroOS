#include <zero/tty.h>
#include <zero/vram.h>

typedef struct {
    FrameBufferInfo frameBufferInfo;
} BootParameter;

void kernel_main(BootParameter *boot_parameter) {
    vram_initialize(&boot_parameter->frameBufferInfo);
    terminal_initialize();
    printf("Hello, kernel!\n");
}
