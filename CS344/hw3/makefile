CC = gcc
CFLAGS = -Wall

default: smallsh

smallsh: main.o smallsh.o
	 $(CC) $(CFLAGS) -o smallsh main.o smallsh.o

main.o: smallsh.c smallsh.h
	$(CC) $(CFLAGS) -c main.c

smallsh.o: smallsh.c smallsh.h
	$(CC) $(CFLAGS) -c smallsh.c

clean:
	$(RM) smallsh *.0 *~
