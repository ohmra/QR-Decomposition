LDLIBS = -lm 
CFLAGS = -Wall -g -O3

ALL: qr_decomp

projet: qr_decomp.o

.PHONY: clean

clean:
	rm -f model validate *.o qr_decomp
	
