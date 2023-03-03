#ifndef _INIT_H
#define _INIT_H

void init_timer0(unsigned char tcnt0_init_value, unsigned char frequency_devision);
void init_timer1(unsigned short tcnt1_init_value, unsigned char frequency_devision);
void init_pin(void);
void init_timer(void);
void init_uart(void);

#endif