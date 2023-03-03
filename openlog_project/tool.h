#ifndef _TOOL_H
#define _TOOL_H

#define SETBIT(PORT, bit)    PORT |= (1 << bit)
#define CLRBIT(PORT, bit)    PORT &= ~(1 << bit)
#define IVTBIT(PORT, bit)    PORT ^= (1 << bit) //·´×ª

#define BLINK_LED_500MS     (0x01)
#define BLINK_LED_2S        (0x02)

/* 
Table 15-6. Clock Select Bit Description
    CS12 CS11 CS10 Description
    0    0    0    No clock source (Timer/Counter stopped).
    0    0    1    clkI/O/1 (no prescaling)
    0    1    0    clkI/O/8 (from prescaler)
    0    1    1    clkI/O/64 (from prescaler)
    1    0    0    clkI/O/256 (from prescaler)
    1    0    1    clkI/O/1024 (from prescaler)
    1    1    0    External clock source on T1 pin. Clock on falling edge.
    1    1    1    External clock source on T1 pin. Clock on rising edge.
*/
#define FREQUENCY_DIVISION_1    (0x01)
#define FREQUENCY_DIVISION_8    (0x02)
#define FREQUENCY_DIVISION_64   (0x03)
#define FREQUENCY_DIVISION_256  (0x04)
#define FREQUENCY_DIVISION_1024 (0x05)

#endif