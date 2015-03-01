SRC := src
BIN := bin
INC := include
BLD := build

all: $(BIN)/sicasm

$(BIN)/sicasm: $(BLD)/sicasm.o $(BLD)/hash_table.o
	mkdir -p $(BIN)
	gcc $(BLD)/sicasm.o $(BLD)/hash_table.o -o $(BIN)/sicasm

$(BLD)/sicasm.o: $(SRC)/sicasm.c
	mkdir -p $(BLD)
	gcc -c $(SRC)/sicasm.c -o $(BLD)/sicasm.o

$(BLD)/hash_table.o: $(SRC)/hash_table.c $(INC)/hash_table.h
	gcc -c $(SRC)/hash_table.c -o $(BLD)/hash_table.o 

clean:
	rm -rf *.o *.gch
