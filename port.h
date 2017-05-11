#ifndef __PORT_H__
#define __PORT_H__

#include <stdint.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif // __PORT_H__
