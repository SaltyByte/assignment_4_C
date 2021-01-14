# -*- MakeFile -*-

CC = gcc
AR = ar
CFLAGS = -Wall

all: frequency

frequency: frequency.c
	$(CC) $(CFLAGS)  frequency.c -o frequency

.PHONY: clean all

clean:
	rm -f frequency
