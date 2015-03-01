all: sicasm

sicasm: sicasm.o hash_table.o
	gcc sicasm.o hash_table.o -o sicasm

sicasm.o: sicasm.c
	gcc sicasm.c -c

hash_table.o: hash_table.c hash_table.h
	gcc hash_table.c hash_table.h -c

clean:
	rm -rf *.o *.gch
