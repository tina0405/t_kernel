#include <serial_port.h>
int calc_divisor (void)
{
	return (CFG_NS16550_CLK / 16 /115200);
}

void t_uart_puts (const char *s)
{
	while(*s){
	     NS16550_putc(*s++);
	}
}

void NS16550_putc (char c)
{
	if (c == '\n')
		NS16550_putc ('\r');
	while ((serial_ports[2]->lsr & LSR_THRE) == 0);
	serial_ports[2]->thr = c;
}

char NS16550_getc (void)
{
	while ((serial_ports[2]->lsr & LSR_DR) == 0);
	return (serial_ports[2]->rbr);
}

int NS16550_tstc (void)
{
	return ((serial_ports[2]->lsr & LSR_DR) != 0);
}

void NS16550_reinit (int baud_divisor)
{
	serial_ports[2]->ier = 0x00;
	serial_ports[2]->lcr = LCR_BKSE;
	serial_ports[2]->dll = baud_divisor & 0xff;
	serial_ports[2]->dlm = (baud_divisor >> 8) & 0xff;
	serial_ports[2]->lcr = LCRVAL;
	serial_ports[2]->mcr = MCRVAL;
	serial_ports[2]->fcr = FCRVAL;
}





