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
