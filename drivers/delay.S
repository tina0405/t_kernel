/*
 *  linux/arch/arm/lib/delay.S
 *
 *  Copyright (C) 1995, 1996 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

		.text

.LC0:		.word	loops_per_jiffy
.LC1:		.word	(2199023*128)>>11 //HZ = 128
/*
 * r0  <= 2000
 * lpj <= 0x01ffffff (max. 3355 bogomips)
 * HZ  <= 1000
 */
.global __udelay;
.global __const_udelay;
.global __delay;
__udelay:
		ldr	r2, .LC1   //r2= (2199023*256)>>11
		mul	r0, r2, r0 //r0 = n*r2
		
__const_udelay:				@ 0 <= r0 <= 0x7fffff06
		mov	r1, #-1    //r1 = -1
		ldr	r2, .LC0   //r2 = lpj			
		ldr	r2, [r2]   		@ max = 0x01ffffff		
		add	r0, r0, r1, lsr #32-14
		mov	r0, r0, lsr #14		@ max = 0x0001ffff
		add	r2, r2, r1, lsr #32-10
		mov	r2, r2, lsr #10		@ max = 0x00007fff
		mul	r0, r2, r0		@ max = 2^32-1
		add	r0, r0, r1, lsr #32-6 //shift right 
		movs	r0, r0, lsr #6 //Data processing to PC with S bit Set
		moveq	pc, lr 
/*
 * loops = r0 * HZ * loops_per_jiffy / 1000000
 *
 * Oh, if only we had a cycle counter...
 */

@ Delay routine
__delay:
		subs	r0, r0, #1
		bhi	__delay
		mov	pc, lr //link register
                
