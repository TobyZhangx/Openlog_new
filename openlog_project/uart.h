#ifndef _UART_H
#define _UART_H

int handle_input(unsigned char *recv_data, unsigned char recv_data_index);
void uart_send_str(unsigned char *str, unsigned char len);
void uart_send_char(unsigned char data);
void change_led_status(void);
void uart_main(void);


#endif