SRC := src
BIN := bin
INC := include
BLD := build
CC  := gcc -Wall -W
TST := test

all: $(BIN)/sicasm

$(BIN)/sicasm: $(BLD)/sicasm.o $(BLD)/hash_table.o $(BLD)/pass_1.o $(BLD)/pass_2.o $(BLD)/gen_ops.o $(BLD)/stack.o $(BLD)/error.o
	mkdir -p $(BIN)
	$(CC) $(BLD)/sicasm.o $(BLD)/hash_table.o $(BLD)/gen_ops.o $(BLD)/pass_1.o $(BLD)/pass_2.o $(BLD)/stack.o $(BLD)/error.o -o $(BIN)/sicasm

$(BLD)/sicasm.o: $(SRC)/sicasm.c $(INC)/sicasm.h 
	mkdir -p $(BLD)
	$(CC) -c $(SRC)/sicasm.c -o $(BLD)/sicasm.o

$(BLD)/hash_table.o: $(SRC)/hash_table.c $(INC)/hash_table.h
	$(CC) -c $(SRC)/hash_table.c -o $(BLD)/hash_table.o 

$(BLD)/pass_1.o: $(SRC)/pass_1.c $(INC)/pass_1.h
	$(CC) -c $(SRC)/pass_1.c -o $(BLD)/pass_1.o 

$(BLD)/pass_2.o: $(SRC)/pass_2.c $(INC)/pass_2.h
	$(CC) -c $(SRC)/pass_2.c -o $(BLD)/pass_2.o 

$(BLD)/gen_ops.o: $(SRC)/gen_ops.c $(INC)/gen_ops.h
	$(CC) -c $(SRC)/gen_ops.c -o $(BLD)/gen_ops.o 

$(BLD)/stack.o: $(SRC)/stack.c $(INC)/stack.h
	$(CC) -c $(SRC)/stack.c -o $(BLD)/stack.o 

$(BLD)/error.o: $(SRC)/error.c $(INC)/error.h
	$(CC) -c $(SRC)/error.c -o $(BLD)/error.o 

test: $(BIN)/sicasm $(TST)/test.o
	mkdir -p $(TST)/$(BIN)
	$(CC) $(TST)/test.o $(BLD)/hash_table.o $(BLD)/gen_ops.o $(BLD)/pass_1.o $(BLD)/stack.o -o $(TST)/$(BIN)/test

$(TST)/test.o: $(TST)/test.c
	$(CC) -c $(TST)/test.c -o $(TST)/test.o
 
clean:
	rm -rf $(BLD) $(BIN)
