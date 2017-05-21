#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdint.h>

#define BUFFER_SIZE         255
#define SCANCODE_COUNT      255

void KEYBOARD_init(void);
void KEYBOARD_push(uint8_t key);
uint8_t KEYBOARD_pop(void);

void handleKeyPress(uint8_t key);

#endif // __KEYBOARD_H__
