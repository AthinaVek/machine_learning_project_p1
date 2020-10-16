all: lsh

lsh: lsh.o help_functions.o calculations.o
	g++ lsh.o help_functions.o calculations.o -o lsh

lsh.o: lsh.cpp
	g++ -c lsh.cpp

help_functions.o: help_functions.cpp
	g++ -c help_functions.cpp

calculations.o: calculations.cpp
	g++ -c calculations.cpp

clean:
	rm -f lsh help_functions calculations lsh.o help_functions.o calculations.o