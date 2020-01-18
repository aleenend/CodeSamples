CC = gcc
CFLAGS = -Wall

compile:	encode.out

encode.out: encode.c driver.c
	$(CC) $(CFLAGS) -o encode.out encode.c driver.c

run: encode.out
	./encode.out tiger.ppm output.ppm

clean:
	rm *.out
	rm output.ppm
