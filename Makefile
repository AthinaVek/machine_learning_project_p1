all: lsh

lsh: lsh.o help_functions.o calculations.o hash_table.o
	g++ lsh.o help_functions.o calculations.o hash_table.o -o lsh

lsh.o: lsh.cpp
	g++ -c lsh.cpp

help_functions.o: help_functions.cpp
	g++ -c help_functions.cpp

calculations.o: calculations.cpp
	g++ -c calculations.cpp

hash_table.o: hash_table.cpp
	g++ -c hash_table.cpp

clean:
	rm -f lsh help_functions calculations hash_table lsh.o help_functions.o calculations.o hash_table.o