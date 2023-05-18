CC = g++
CFLAGS = -Wall -std=c++11

INC_DIR = include
SRC_DIR = src

OBJS = $(SRC_DIR)/Scanner.o $(SRC_DIR)/main.o

INC_FLAG = -I$(INC_DIR)

all: Compiler

Compiler: $(OBJS)
	$(CC) $(CFLAGS) $(INC_FLAG) -o $@ $^

$(SRC_DIR)/Scanner.o: $(SRC_DIR)/Scanner.cpp $(INC_DIR)/Scanner.h
	$(CC) $(CFLAGS) $(INC_FLAG) -c -o $@ $<

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/Scanner.h
	$(CC) $(CFLAGS) $(INC_FLAG) -c -o $@ $<

clean:
	rm -f $(SRC_DIR)/*.o Compiler
	rm -f out

test:
	g++ -o Compiler src/Scanner.o src/main.o