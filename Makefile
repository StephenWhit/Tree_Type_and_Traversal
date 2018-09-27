all: TreeDr TreeType.cpp QueType.cpp

TreeDr: TreeDr.o TreeType.o QueType.o
	g++ -Wall -g -o TreeDr TreeDr.o TreeType.o QueType.o

TreeDr.o: TreeDr.cpp
	g++ -Wall -std=c++14 -c -g -O0 -pedantic-errors TreeDr.cpp

TreeType.o: TreeType.cpp
	g++ -Wall -std=c++14 -c -g -O0 -pedantic-errors TreeType.cpp

QueType.o: QueType.cpp
	g++ -Wall -std=c++14 -c -g -O0 -pedantic-errors QueType.cpp

clean:
	-rm -f TreeDr
	-rm -f TreeDr.o
	-rm -f TreeType.o
	-rm -f QueType.o
	