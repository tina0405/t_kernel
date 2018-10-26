#include <drivers/serial_port.h>
unsigned long loops_per_jiffy = (1<<12);
extern void __udelay(unsigned long usecs);

void _start(void){	
	int clock_divisor = calc_divisor(serial_ports[2]);
	NS16550_reinit (serial_ports[2],clock_divisor);
	t_uart_puts("please enter a word!"); 
	char input = NS16550_getc (serial_ports[2]);
	t_uart_puts("\nyour choice is:\n");
	NS16550_putc(serial_ports[2],input);	
	__udelay(1000);
	NS16550_putc(serial_ports[2],input);		
	while(1);
}

