#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include "tool.h"
#include "init.h"

void init_timer0(unsigned char tcnt0_init_value, unsigned char frequency_devision)
{
    /* ��ʱ��0ʹ������ģʽ */
    TCCR0B = frequency_devision; //��16MHzʱ��Ƶ�ʽ��з�Ƶ
    TCNT0 = tcnt0_init_value; //���ö�ʱ��0��ֵ
    TIMSK0 &= ~(1<<TOIE0); //�رն�ʱ��/������0�ж�
    
    return;
}

void init_timer1(unsigned short tcnt1_init_value, unsigned char frequency_devision)
{
    /* ��ʱ��1ʹ������ģʽ */
	TCCR1A = 0x00;
    TCCR1B = frequency_devision; //��16MHzʱ��Ƶ�ʽ��з�Ƶ
    TCNT1 = tcnt1_init_value; //���ö�ʱ��1��ֵ
	TIMSK1 = 0x00;
    TIMSK1 &= ~(1<<TOIE1); //�رն�ʱ��/������1�ж�
    
    return;
}

void init_pin()
{
    SETBIT(DDRB, DDB5);//PORTB5������Ϊ�������
    CLRBIT(PORTB, PORTB5); //PORTB5������Ϊ�͵�ƽ
    return;
}

void init_timer()
{
    init_timer0(0x05, FREQUENCY_DIVISION_64);//��ʱ��0��ʱ4ms��������ֵ��Ϊ0x05, 64��Ƶ
    init_timer1(0x85ED, FREQUENCY_DIVISION_256);//��ʱ��1��ʱ1s��������ֵ��Ϊ0xB1DF, 256��Ƶ
    return;
}

void init_uart()
{
    //������������ж�ʹ��, �������ա�����ʹ��
    UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);

    //��Ϊ����ģʽ���첽����У�顢1λֹͣλ��8λ����λ
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
    /*
        ����������Ϊ38400��
        �����¹�ʽ����UBBR0
        UBBR0 = F_CPU/(16*BaudRate) - 1
    */
    UBRR0H = 0x00;
    UBRR0L = 0x67;
	
    return;
}