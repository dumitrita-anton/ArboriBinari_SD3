CC = gcc
CFLAGS=-Wall -Wextra -g

build: clean tema3

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tema3.exe: tema3.o arb.o
	$(CC) $(CFLAGS) $^ -o $@

tema3: tema3.o arb.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean checkMem

clean:
	rm -f *.o tema3 tema3.o arb.o

checkMem:
	valgrind --leak-check=yes --track-origins=yes ./tema3