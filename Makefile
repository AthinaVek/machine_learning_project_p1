all: lsh cube

lsh: lsh.o help_functions.o calculations.o
	g++ lsh.o help_functions.o calculations.o -o lsh

cube: cube.o help_functions.o calculations.o calculations_cube.o
	g++ cube.o help_functions.o calculations.o calculations_cube.o -o cube

lsh.o: lsh.cpp
	g++ -c lsh.cpp

cube.o: cube.cpp
	g++ -c cube.cpp

help_functions.o: help_functions.cpp
	g++ -c help_functions.cpp

calculations.o: calculations.cpp
	g++ -c calculations.cpp

calculations_cube.o: calculations_cube.cpp
	g++ -c calculations_cube.cpp

clean:
	rm -f lsh cube help_functions calculations calculations_cube lsh.o cube.o help_functions.o calculations.o calculations_cube.o
