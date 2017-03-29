CFLAGS = -Wall -pedantic
CCF = $(CC) 

all: life
	./life input/glider_gun.png

life: main.o
	$(CCF) -o life src/main.o src/grid.o src/simulator.o src/png_reader.o -lpng
	
main.o: src/main.c grid.o simulator.o png_reader.o
	$(CCF) -c -o src/main.o src/main.c

grid.o: src/grid.c src/grid.h
	$(CCF) -c -o src/grid.o src/grid.c

simulator.o: src/simulator.c src/simulator.h grid.o neighbourhoods.o
	$(CCF) -c -o src/simulator.o src/simulator.c -l neighbourhoods.o

neighbourhoods.o: src/neighbourhoods.c src/neighbourhoods.h grid.o
	$(CCF) -c -o src/neighbourhoods.o src/neighbourhoods.c

png_reader.o: src/png_reader.c src/png_reader.h grid.o
	$(CCF) -c -o src/png_reader.o src/png_reader.c

.PHONY: clean
clean:
	-rm life
	-rm src/*.o
