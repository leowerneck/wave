CC = gcc
CFLAGS = -O0 -march=native -g -Wall -Werror
LDFLAGS = -lm

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
INC = wave.h

all: wave

wave: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) wave
