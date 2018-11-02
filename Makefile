CC = /home/hao/jorjin_bsp/mydroid/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-gcc
LD = /home/hao/jorjin_bsp/mydroid/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-ld
OBJCPY = /home/hao/jorjin_bsp/mydroid/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/arm-eabi-objcopy
MKIMG = ../u-boot/tools/mkimage
SYS_INCLUDE = /home/hao/jorjin_bsp/mydroid/prebuilts/gcc/linux-x86/arm/arm-eabi-4.6/bin/../lib/gcc/arm-eabi/4.6.x-google/include
ENTRY = 0x80008840
LOAD_ADDR = 0x80008000
all: uImage

compile_start: 
	$(CC) -g -Os -I./ -fno-strict-aliasing -fno-common -ffixed-r8 -msoft-float -fno-builtin -ffreestanding -nostdinc -isystem $(SYS_INCLUDE) -pipe -mabi=apcs-gnu -Wall -Wstrict-prototypes -c -o start.o start.c
compile_drivers:
	$(CC) -g -Os -I./drivers/ -fno-strict-aliasing -fno-common -ffixed-r8 -msoft-float -fno-builtin -ffreestanding -nostdinc -isystem $(SYS_INCLUDE) -pipe -mabi=apcs-gnu -Wall -Wstrict-prototypes -c -o drivers/serial_port.o drivers/serial_port.c
	$(CC) -g -Os -fno-strict-aliasing -fno-common -ffixed-r8 -msoft-float -fno-builtin -ffreestanding -nostdinc -I./ -isystem $(SYS_INCLUDE)  -pipe -mabi=apcs-gnu -Wall -Wstrict-prototypes -c -o drivers/delay.o drivers/delay.S
	$(CC) -g -Os -nostdinc -isystem $(SYS_INCLUDE) -I/home/hao/jorjin_bsp/kernel/android-3.4/arch/arm/include -I./ -Iinclude  -include /home/hao/jorjin_bsp/kernel/android-3.4/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -D__ASSEMBLY__ -mabi=apcs-gnu -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float -gdwarf-2 -Wa,-march=all -DTEXT_OFFSET=0x00008000 -c -o drivers/head.o drivers/head.S
linker: compile_start compile_drivers
	$(LD) -EL -p --no-undefined -X --build-id -o t_kernel drivers/head.o start.o drivers/serial_port.o drivers/delay.o -T linkerscript -Map t_kernel.map
binary: linker
	$(OBJCPY) -g -O binary t_kernel t_kernel.bin
uImage: binary
	$(MKIMG) -A arm -T kernel -C none -a $(LOAD_ADDR) -e $(ENTRY) -n "t_program" -d t_kernel.bin uImage

clean: 
	$(RM) -r t_kernel *.o *.map ./drivers/*.o uImage *.bin

.PHONY: clean
