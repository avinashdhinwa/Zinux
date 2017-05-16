#ifndef __PORT_H__
#define __PORT_H__

#include <stdint.h>

#define PORT_PIC_MASTER_A           0x20
#define PORT_PIC_MASTER_B           0x21
#define PORT_PIC_SLAVE_A            0xA0
#define PORT_PIC_SLAVE_B            0xA1

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif // __PORT_H__
