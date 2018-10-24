#define LSR_THRE 0x20
#define thr rbr
#define NULL ((void *)0)
#define CFG_NS16550_COM3 OMAPP44XX_UART3
#define OMAPP44XX_UART3 (OMAP44XX_L4_PER+0x20000)
#define OMAP44XX_L4_PER 0x48000000
#define LCR_BKSE	0x80		/* Bank select enable */
#define LCRVAL LCR_8N1
#define LCR_8N1 0x03
#define dll rbr
#define dlm ier
#define MCRVAL (MCR_DTR | MCR_RTS)
#define MCR_DTR         0x01
#define MCR_RTS         0x02			/* RTS/DTR */
#define CFG_NS16550_CLK 48000000
#define ERRATA_I202_TIMEOUT 5
#define LSR_DATA_INOUT (LSR_DR | LSR_TEMT | LSR_THRE)
#define LSR_DR 0x01
#define LSR_TEMT 0x40
#define LSR_DATA_EMPTY (LSR_TEMT | LSR_THRE)
#define FCRVAL (FCR_FIFO_EN | FCR_RXSR | FCR_TXSR)	/* Clear & enable FIFOs */


#define FCR_FIFO_EN     0x01		/* Fifo enable */
#define FCR_RXSR        0x02		/* Receiver soft reset */
#define FCR_TXSR        0x04		/* Transmitter soft reset */

struct NS16550 {
	unsigned char rbr;		/* 0 */
	int pad1:24;
	unsigned char ier;		/* 1 */
	int pad2:24;
	unsigned char fcr;		/* 2 */
	int pad3:24;
	unsigned char lcr;		/* 3 */
	int pad4:24;
	unsigned char mcr;		/* 4 */
	int pad5:24;
	unsigned char lsr;		/* 5 */
	int pad6:24;
	unsigned char msr;		/* 6 */
	int pad7:24;
	unsigned char tlr;		/* 7 */
	int pad8:24;
	unsigned char mdr1;		/* 8 mode select reset TL16C750*/
	int pad9:24;
	unsigned int pad[12];		/* 9 - 20 */
	unsigned char sysc;		/* 21 */
	int pad10:24;
	unsigned char syss;		/* 22 */
} __attribute__ ((packed));
typedef volatile struct NS16550 *NS16550_t;
static NS16550_t serial_ports[4] = {
	NULL,
	NULL,
	(NS16550_t)CFG_NS16550_COM3,
	NULL
};
int calc_divisor (NS16550_t port);
void t_uart_puts (const char *s);
void NS16550_putc (NS16550_t com_port, char c);
void NS16550_reinit(NS16550_t com_port, int baud_divisor);
char NS16550_getc (NS16550_t com_port);

