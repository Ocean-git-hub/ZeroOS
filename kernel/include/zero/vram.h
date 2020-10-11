#ifndef ZEROOS_VRAM_H
#define ZEROOS_VRAM_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    size_t frameBufferBase, frameBufferSize, screenHeight, screenWidth;
} FrameBufferInfo;

void vram_initialize(FrameBufferInfo *frameBufferInfo);

void vram_draw_pixel(size_t x, size_t y, uint32_t color);

void vram_fill_box(size_t x1, size_t y1, size_t x2, size_t y2, uint32_t color);

void vram_fill_screen(uint32_t color);

size_t vram_get_screen_w();

size_t vram_get_screen_h();

#endif //ZEROOS_VRAM_H
