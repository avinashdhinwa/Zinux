#include "tty.h"

#include "vga.h"

static int16_t *vgaBuffer = (int16_t*)VGA_BUFFER;
static uint8_t cursorX = 0;
static uint8_t cursorY = 0;
static uint8_t color = 0x0F;            // White on black color

void TTY_init(void)
{
    uint16_t i;
    for(i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        *(vgaBuffer + i) = (color << 8) | ' ';

}

void TTY_setColor(const uint8_t background, const uint8_t foreground)
{
    color = ((background & 0x0F) << 4) | foreground & 0x0F;
}

void TTY_changeColor(const uint8_t background, const uint8_t foreground)
{
    uint16_t i;

    TTY_setColor(background, foreground);
    for(i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        *(vgaBuffer + i) = (*(vgaBuffer + i) & 0x00FF) | (color << 8);
}

void TTY_putchar(const char ch)
{
    if(ch == '\n')
    {
        TTY_moveCursor(0, cursorY + 1);
        return;
    }
    if(ch == '\t')
    {
        TTY_moveCursor(cursorX + 8, cursorY);
        return;
    }

    uint16_t index = cursorY * SCREEN_WIDTH + cursorX;
    *(vgaBuffer + index) = (color << 8) | ch;

    TTY_moveCursor(cursorX + 1, cursorY);
}

void TTY_puts(const char *str)
{
    for(; *str != '\0'; str++)
        TTY_putchar(*str);
}

void TTY_moveCursor(const uint8_t x, const uint8_t y)
{
    cursorX = x;
    cursorY = y;

    if(cursorX >= SCREEN_WIDTH)
    {
        cursorX = 0;
        cursorY++;
    }
    if(cursorY >= SCREEN_HEIGHT)
    {
        TTY_scrollScreen();
        cursorY = SCREEN_HEIGHT - 1;
    }
}

void TTY_scrollScreen(void)
{
    uint16_t i;

    for(i = 0; i < SCREEN_WIDTH * (SCREEN_HEIGHT - 1); i++)
        *(vgaBuffer + i) = *(vgaBuffer + i + SCREEN_WIDTH);
    for(; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
        *(vgaBuffer + i) = (color << 8) | ' ';
}
