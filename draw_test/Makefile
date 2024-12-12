all: libLcd.a test.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

libLcd.a: ../lcdLib/font-11x16.o ../lcdLib/font-5x7.o ../lcdLib/font-8x12.o ../lcdLib/lcdutils.o ../lcdLib/lcddraw.o
	$(AR) crs $@ $^

lcddraw.o: ../lcdLib/lcddraw.c ../lcdLib/lcddraw.h ../lcdLib/lcdutils.h
lcdutils.o: ../lcdLib/lcdutils.c ../lcdLib/lcdutils.h

install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

test.elf: test.o libLcd.a
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer

load: test.elf
	msp430loader.sh $^

clean:
	rm -f libLcd.a *.o *.elf
