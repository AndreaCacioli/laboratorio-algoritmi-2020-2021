library: edit.h edit.c
	gcc -c edit.h edit.c

unit: UnitTests.c
	gcc -c UnitTests.c

run: edit.o UnitTests.o
	gcc edit.o UnitTests.o -o Ex2
	./Ex2

demofile: FileDemo.c
	gcc -c FileDemo.c

filereader: edit.o FileDemo.o
	gcc edit.o FileDemo.o -o FileDemo
	./FileDemo

clean:
	rm -f *.o