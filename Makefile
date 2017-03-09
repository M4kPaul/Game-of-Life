CFLAGS = -Wall -pedantic
CCF = $(CC) $(CFLAGS)

all: life
	./life

life: main.o
	$(CCF) -o life src/main.o
	
main.o: src/main.c
	$(CC) -c -o src/main.o src/main.c

.PHONY: clean
clean:
	-rm life
	-rm src/*.o