all: test.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS 	= -L/opt/ti/msp430_gcc/include -L../lib 
#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

test.c: libTimer.h lcdutils.h lcddraw.h

test.o: test.c libTimer.h lcdutils.h lcddraw.h

test.elf: test.o libTimer.h lcdutils.h lcddraw.h
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ -lTimer

load: test.elf
	msp430loader.sh $^

clean:
	rm -f libLcd.a *.o *.elf
