#include <zero/tty.h>
#include <zero/vram.h>
#include <zero/font.h>

#include <stdio.h>
#include <string.h>

size_t terminal_row;
size_t terminal_column;
size_t terminal_w;
size_t terminal_h;
uint8_t *terminal_font;
size_t terminal_font_w;
size_t terminal_font_h;
size_t terminal_font_num_char;
uint32_t terminal_front_color;
uint32_t terminal_back_color;

void terminal_initialize() {
    terminal_front_color = 0xffffff;
    terminal_back_color = 0;
    vram_fill_screen(terminal_back_color);
    terminal_column = terminal_row = 0;
    terminal_h = vram_get_screen_h();
    terminal_w = vram_get_screen_w();
    terminal_font = (uint8_t *) &default_font;
    terminal_font_h = FONT_DEFAULT_FONT_H;
    terminal_font_w = FONT_DEFAULT_FONT_W;
    terminal_font_num_char = FONT_DEFAULT_FONT_NUM_CHAR;
}

void terminal_putc_at(char c, size_t x, size_t y) {
    uint8_t *put_font = &terminal_font[(c - 0x20) * terminal_font_h];
    for (size_t f_y = 0; f_y < terminal_font_h; ++f_y) {
        uint8_t font_v = put_font[f_y];
        for (size_t f_x = 0; f_x < terminal_font_w; ++f_x) {
            if ((font_v >> (terminal_font_w - f_x - 1)) & 1u)
                vram_draw_pixel(x + f_x, y + f_y, terminal_front_color);
            else
                vram_draw_pixel(x + f_x, y + f_y, terminal_back_color);
        }
    }
}

void terminal_putc(char c) {
    if (c == '\n') {
        terminal_column = 0;
        terminal_row += terminal_font_h;
    } else if (c == '\t')
        terminal_write_string("    ");
    else {
        terminal_putc_at(c, terminal_column, terminal_row);
        terminal_column += terminal_font_w;
        if (terminal_column > terminal_w) {
            terminal_column = 0;
            terminal_row += terminal_font_h;
            if (terminal_row > terminal_h)
                terminal_column = 0;
        }
    }
}

void terminal_write(const char *s, size_t size) {
    for (size_t i = 0; i < size && *s; ++i)
        terminal_putc(s[i]);
}

void terminal_write_string(const char *s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len; ++i)
        terminal_putc(s[i]);
}

void terminal_puts(const char *s) {
    terminal_write_string(s);
    terminal_putc('\n');
}

int kprintf(const char *format, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, format);
    int len = vsprintf(buffer, format, args);
    va_end(args);
    terminal_write_string(buffer);
    return len;
}
