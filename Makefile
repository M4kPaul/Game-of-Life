CFLAGS = -Wall -pedantic
CCF = $(CC) $(CFLAGS)
PATHS = src/bmp-reader

all: life
	./life input/glider_gun.bmp

life: main.o
	$(CCF) -o life src/main.o src/bmp-reader/bmp_reader.o
	
main.o: src/main.c bmp_reader.o
	$(CC) -I $(PATHS) -c -o src/main.o src/main.c

bmp_reader.o: src/bmp-reader/bmp_reader.c src/bmp-reader/bmp_reader.h
	$(CCF) -c -o src/bmp-reader/bmp_reader.o src/bmp-reader/bmp_reader.c

.PHONY: clean
clean:
	-rm life
	-rm src/*.o
	-rm src/bmp-reader/*.o

