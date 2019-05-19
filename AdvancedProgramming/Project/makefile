a.out: main.o BfsSearch.o Node.o PointNode.o Map.o Point.o
	g++ -o a.out main.o BfsSearch.o Node.o PointNode.o Map.o Point.o

main.o: main.cpp BfsSearch.h Node.h PointNode.h Map.h Point.h
	g++ -c -o main.o main.cpp

BfsSearch.o: BfsSearch.cpp
	g++ -c -o BfsSearch.o BfsSearch.cpp

Node.o: Node.cpp
	g++ -c -o Node.o Node.cpp

PointNode.o: PointNode.cpp
	g++ -c -o PointNode.o PointNode.cpp

Map.o: Map.cpp
	g++ -c -o Map.o Map.cpp

clean: rm -f *.o a.out
