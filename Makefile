LDLIBS = -lm 
CFLAGS = -Wall -g -O3

ALL: projet

projet: projet.o

.PHONY: clean

clean:
	rm -f model validate *.o
	
