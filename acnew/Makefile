CC=gcc
TARGET=all

all:acsmx

acsmx:entry.c acsmx.c 
	$(CC) -g -o $@ $^ -Wall 

clean:
	rm -f acsmx
