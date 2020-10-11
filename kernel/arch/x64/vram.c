#include <zero/vram.h>

FrameBufferInfo frameBufferInfo;
size_t screen_w;
uint32_t *bufferPixelBase;

void vram_initialize(FrameBufferInfo *_frameBufferInfo) {
    frameBufferInfo = *_frameBufferInfo;
    screen_w = _frameBufferInfo->screenWidth;
    bufferPixelBase = (uint32_t *) _frameBufferInfo->frameBufferBase;
}

inline __attribute__((always_inline)) void vram_draw_pixel(size_t x, size_t y, uint32_t color) {
    bufferPixelBase[x + y * screen_w] = color;
}

void vram_fill_box(size_t x1, size_t y1, size_t x2, size_t y2, uint32_t color) {
    for (uint64_t y = y1; y < y2; ++y)
        for (uint64_t x = x1; x < x2; ++x)
            vram_draw_pixel(x, y, color);
}

void vram_fill_screen(uint32_t color) {
    vram_fill_box(0, 0, screen_w - 1, frameBufferInfo.screenHeight - 1, color);
}

size_t vram_get_screen_w() {
    return frameBufferInfo.screenWidth;
}

size_t vram_get_screen_h() {
    return frameBufferInfo.screenHeight;
}
