all : main

main : main.o list.o hash.o bitmap.o
	gcc -o testlib main.o list.o hash.o bitmap.o
main.o : main.c
	gcc -c main.c
list.o : list.c
	gcc -c list.c
hash.o : hash.c
	gcc -c hash.c
bitmap.o : bitmap.c
	gcc -c bitmap.c
clean:
	rm -f *.o testlib

