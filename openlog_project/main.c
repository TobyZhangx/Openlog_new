/*
 * openlog_project.c
 *
 * Created: 2023/3/1 17:37:58
 * Author : tbz
 */ 

#include <avr/io.h>
#include "init.h"
#include "uart.h"

int main(void)
{
    init_pin();
    init_timer();
    uart_main();
    
    return 0;    
}

