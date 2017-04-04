FLAGS = -Wall -pedantic
LIBS = -lpng -lpthread

life: src/bitmap.o src/bmp_reader.o src/grid.o src/iocontrol.o src/main.o \
	  src/neighbourhoods.o src/png_reader.o src/png_writer.o src/simulator.o
	cc -o life $^ $(LIBS) $(FLAGS) 

test0: life
	./life -M 300 -p input/glider_gun.png -p output/ 
test1: life
	./life -M 100 -p input/test1.png -p output/
test2: life
	./life -M 100 -p input/test2.png -p output/ -t 100
test3: life
	./life -M 2000 -p input/puffer.png -p output/ -t 1

bitmap.o: src/bitmap.c src/bitmap.h
	cc -c src/bitmap.c

bmp_reader.o: src/bmp_reader.c src/bmp_reader.h src/grid.h
	cc -c src/bmp_reader.c

grid.o: grid.c grid.h 
	cc -c src/grid.c 

iocontrol.o: src/iocontrol.c src/iocontrol.h src/bmp_reader.h \
			 src/grid.h src/png_reader.h src/png_writer.h
	cc -c src/iocontrol.c

main.o: src/main.c src/grid.h src/iocontrol.h
	cc -c src/main.c

neighbourhoods.o: src/neighbourhoods.c src/neighbourhoods.h src/grid.h
	cc -c src/neighobourhoods.c

png_reader.o: src/png_reader.c src/png_reader.h src/bitmap.h src/grid.h
	cc -c src/png_reader.c

png_writer.o: src/png_writer.c src/png_writer.h src/bitmap.h src/grid.h
	cc -c src/png_writer.c

simulator.o: src/simulator.c src/simulator.h src/grid.h src/iocontrol.h src/neighbourhoods.h
	cc -c src/simulator.c

clean:
	rm life
	rm -f src/*.o
clean_output:
	rm -f output/*
