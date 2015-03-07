SRC := src
BIN := bin
INC := include
BLD := build
CC  := gcc
TST := test

all: $(BIN)/sicasm

$(BIN)/sicasm: $(BLD)/sicasm.o $(BLD)/hash_table.o
	mkdir -p $(BIN)
	$(CC) $(BLD)/sicasm.o $(BLD)/hash_table.o -o $(BIN)/sicasm

$(BLD)/sicasm.o: $(SRC)/sicasm.c $(INC)/sicasm.h
	mkdir -p $(BLD)
	$(CC) -c $(SRC)/sicasm.c -o $(BLD)/sicasm.o

$(BLD)/hash_table.o: $(SRC)/hash_table.c $(INC)/hash_table.h
	$(CC) -c $(SRC)/hash_table.c -o $(BLD)/hash_table.o 

test: $(TST)/test.o
	mkdir -p $(TST)/$(BIN)
	$(CC) $(TST)/test.o -o $(TST)/$(BIN)/test

$(TST)/test.o: $(TST)/test.c
	$(CC) -c $(TST)/test.c -o $(TST)/test.o
 
clean:
	rm -rf $(BLD) $(BIN)
