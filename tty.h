#ifndef __TTY_H__
#define __TTY_H__

#include <stdint.h>

void TTY_init(void);
void TTY_setColor(const uint8_t background, const uint8_t foreground);
void TTY_changeColor(const uint8_t background, const uint8_t foreground);
void TTY_putchar(const char ch);
void TTY_puts(const char *str);
void TTY_moveCursor(const uint8_t x, const uint8_t y);
void TTY_scrollScreen(void);

#endif // __TTY_H__
