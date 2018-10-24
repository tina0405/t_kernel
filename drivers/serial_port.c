#include <serial_port.h>
int calc_divisor (NS16550_t port)
{
	return (CFG_NS16550_CLK / 16 /115200);
}

void t_uart_puts (const char *s)
{
	while(*s){
	     NS16550_putc(serial_ports[2],*s++);
	}
}

void NS16550_putc (NS16550_t com_port, char c)
{
	if (c == '\n')
		NS16550_putc (serial_ports[2], '\r');
	while (( com_port->lsr & LSR_THRE) == 0);
	com_port->thr = c;
}

char NS16550_getc (NS16550_t com_port)
{
	while ((com_port->lsr & LSR_DR) == 0);
	return (com_port->rbr);
}

int NS16550_tstc (NS16550_t com_port)
{
	return ((com_port->lsr & LSR_DR) != 0);
}

void NS16550_reinit (NS16550_t com_port, int baud_divisor)
{
	com_port->ier = 0x00;
	com_port->lcr = LCR_BKSE;
	com_port->dll = baud_divisor & 0xff;
	com_port->dlm = (baud_divisor >> 8) & 0xff;
	com_port->lcr = LCRVAL;
	com_port->mcr = MCRVAL;
	com_port->fcr = FCRVAL;
}





