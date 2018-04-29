all: encode

encode: main.o tree.o heap.o
	g++ main.o tree.o heap.o -o encode
	rm -rf *o

main.o: main.cpp
	g++ -c main.cpp

tree.o: tree.cpp
	g++ -c tree.cpp 

heap.o: heap.cpp
	g++ -c heap.cpp 

clean:
	rm -rf *o encode
