#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tool.h"
#include "uart.h"
#include "init.h"

unsigned char recv_data[256]; //�洢���յ�����
volatile unsigned char recv_data_index = 0; //��¼�洢��һλ�������ݵ��±�
volatile unsigned char cnt = 0; //��¼��ʱ��1��ǰ�����˶��ٸ�
volatile unsigned char blink_led_interval = 0; //led��������

ISR(TIMER0_OVF_vect)
{
    TCNT0 = 0x05;
    cnt++;
    change_led_status();
}

ISR(TIMER1_OVF_vect)
{
	unsigned char temp = 0x00;
	temp = TIFR1;
	uart_send_str("TIFR12:", 7);
	uart_send_char(temp);
	uart_send_str("\r\n", 2);
	unsigned char temp2 = 0x00;
	temp2 = TIMSK1;
	uart_send_str("TIMSK12:", 8);
	uart_send_char(temp2);
	uart_send_str("\r\n", 2);
    TIMSK1 = 0x00; //�رն�ʱ��/������1�ж� 
    TCNT1 = 0x85ED;

    if (-1 == handle_input(recv_data, recv_data_index))
    {
        uart_send_str("Unknown cmd:", 12);
        uart_send_str(recv_data, recv_data_index);
        uart_send_str("\r\n", 2);
        //uart_send_str(".Please input:\r\n", 16);
        //uart_send_str("1.LED ON\r\n", 10);
        //uart_send_str("2.LED OFF\r\n", 11);
        //uart_send_str("3.LED HEART\r\n", 13);
        //uart_send_str("4.UART:.....\r\n", 15);
    }
    else
    {
        uart_send_str("cmd:", 4);
        uart_send_str(recv_data, recv_data_index);
        uart_send_str("\r\n", 2);
    }
    recv_data_index = 0;
    memset(recv_data, 0, 256);
}

ISR(USART_RX_vect)
{
    CLRBIT(UCSR0B, RXCIE0);
    if (recv_data_index < 256) 
    {
        recv_data[recv_data_index++] = UDR0;
    }
    SETBIT(UCSR0B, RXCIE0);
	unsigned char temp = 0x00;
	temp = TIFR1;
	uart_send_str("TIFR11:", 7);
	uart_send_char(temp);
	uart_send_str("\r\n", 2);
	unsigned char temp2 = 0x00;
	temp2 = TIMSK1;
	uart_send_str("TIMSK11:", 8);
	uart_send_char(temp2);
	uart_send_str("\r\n", 2);
	TCNT1 = 0x85ED;
    TIMSK1 = (1<<TOIE1); //������ʱ��/������1�ж�
}

void change_led_status()
{
    if (((BLINK_LED_500MS == blink_led_interval) && (125 <= cnt))
        || ((BLINK_LED_2S == blink_led_interval) && (600 <= cnt)))
    {
        IVTBIT(PORTB, PORTB5);
        cnt = 0;
    }
    return;
}


void uart_send_str(unsigned char *str, unsigned char len)
{
    int index = 0;
    while (index < len)
    {
        uart_send_char(str[index]);
        index++;
    }
    return;
}

void uart_send_char(unsigned char data)
{
    while (!(UCSR0A & (1<<UDRE0)));//��ⷢ��buffer�Ƿ�Ϊ��
    UDR0 = data;
    while (!(UCSR0A & (1<<TXC0)));//��������Ƿ��ѷ���
    SETBIT(UCSR0A, TXC0);
    return;
}

int handle_input(unsigned char *recv_data, unsigned char recv_data_index)
{
    if (0 == strncmp(recv_data, "LED ON", 6))
    {
        TIMSK0 &= ~(1<<TOIE0); //�رն�ʱ��/������0�ж�
        SETBIT(PORTB, PORTB5);
    }
    else if (0 == strncmp(recv_data, "LED OFF", 7))
    {
        TIMSK0 &= ~(1<<TOIE0); //�رն�ʱ��/������0�ж�
        CLRBIT(PORTB, PORTB5);
    }
    else if (0 == strncmp(recv_data, "LED HEART", 9))
    {
        blink_led_interval = BLINK_LED_500MS;
        TCNT0 = 0x05;
        cnt = 0;
        TIMSK0 |= (1<<TOIE0); //������ʱ��/������0�ж�    
    }
    else if (0 == strncmp(recv_data, "UART:", 5))
    {
        TIMSK0 &= ~(1<<TOIE0); //�رն�ʱ��/������0�ж�
        uart_send_str(&recv_data[5], recv_data_index-5);
    }
    else
    {
        return -1;
    }
    
    return 0;
}

void uart_main(void)
{
    init_uart();
    memset(recv_data, 0, 256);
    SREG |= (1 << 7); //����ȫ���ж�
	int i=0;
    while(1)
	{
		i++;
	}
    return;
}