library: edit.h edit.c
	gcc -c edit.h edit.c

unit: UnitTests.c
	gcc -c UnitTests.c

run: edit.o UnitTests.o
	gcc edit.o UnitTests.o -o Ex2
	./Ex2

clean:
	rm -f *.o