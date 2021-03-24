UnitTests.o: UnitTests.c
	gcc -c UnitTests.c


mbi.o: mbi.c mbi.h
	gcc -c mbi.c


Ex1: mbi.o  UnitTests.o
	gcc mbi.o UnitTests.o -o Ex1

clean:
	rm -f *.o
	

run:  Ex1
	./Ex1

SortingFromFile.o: SortingFromFile.c
	gcc -c SortingFromFile.c

filereader: mbi.o  SortingFromFile.o
	gcc mbi.o SortingFromFile.o -o SortingFromFile

data:  mbi.o SortingFromFile SortingFromFile.o
	gcc -c mbi.c
	gcc mbi.o SortingFromFile.o -o SortingFromFile
	./SortingFromFile
