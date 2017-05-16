#ifndef __IRQ_H__
#define __IRQ_H__

#include <stdint.h>

#define IRQ_BASE                0x20

uint32_t IRQHandler(uint8_t irq, uint32_t esp);

void IRQ_init(void);
void IRQ_enable(void);
void IRQ_disable(void);

void IRQHandlerIgnore(void);

void IRQHandler00(void);
void IRQHandler01(void);
void IRQHandler02(void);
void IRQHandler03(void);

void ExceptionHandler00(void);
void ExceptionHandler01(void);
void ExceptionHandler02(void);
void ExceptionHandler03(void);

#endif // __IRQ_H__
