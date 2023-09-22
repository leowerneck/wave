CC = gcc
CFLAGS = -O2 -march=native -fopenmp -std=c99

SRC := $(shell find . -type f -name '*.c')
OBJ := $(SRC:.c=.o)
INC = wave.h
EXE = wave

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXE)
