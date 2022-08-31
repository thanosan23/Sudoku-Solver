CC=gcc
CFLAGS = -O2 -g -Wall
CFLAGS += -Wextra -Wpedantic

SRC  = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs main

dirs:
	mkdir -p ./$(BIN)

run: all
	$(BIN)/main

main: $(OBJ)
	$(CC) -o $(BIN)/main $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
