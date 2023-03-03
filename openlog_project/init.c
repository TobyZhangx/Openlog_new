#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include "tool.h"
#include "init.h"

void init_timer0(unsigned char tcnt0_init_value, unsigned char frequency_devision)
{
    /* 定时器0使用正常模式 */
    TCCR0B = frequency_devision; //对16MHz时钟频率进行分频
    TCNT0 = tcnt0_init_value; //设置定时器0初值
    TIMSK0 &= ~(1<<TOIE0); //关闭定时器/计数器0中断
    
    return;
}

void init_timer1(unsigned short tcnt1_init_value, unsigned char frequency_devision)
{
    /* 定时器1使用正常模式 */
	TCCR1A = 0x00;
    TCCR1B = frequency_devision; //对16MHz时钟频率进行分频
    TCNT1 = tcnt1_init_value; //设置定时器1初值
	TIMSK1 = 0x00;
    TIMSK1 &= ~(1<<TOIE1); //关闭定时器/计数器1中断
    
    return;
}

void init_pin()
{
    SETBIT(DDRB, DDB5);//PORTB5引脚设为输出引脚
    CLRBIT(PORTB, PORTB5); //PORTB5引脚设为低电平
    return;
}

void init_timer()
{
    init_timer0(0x05, FREQUENCY_DIVISION_64);//定时器0定时4ms，计数初值设为0x05, 64分频
    init_timer1(0x85ED, FREQUENCY_DIVISION_256);//定时器1定时1s，计数初值设为0xB1DF, 256分频
    return;
}

void init_uart()
{
    //开启接收完成中断使能, 开启接收、发送使能
    UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);

    //设为以下模式：异步、不校验、1位停止位、8位数据位
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
    /*
        波特率设置为38400，
        按以下公式计算UBBR0
        UBBR0 = F_CPU/(16*BaudRate) - 1
    */
    UBRR0H = 0x00;
    UBRR0L = 0x67;
	
    return;
}