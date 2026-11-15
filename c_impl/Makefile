CC := cc
CFLAGS := -std=c11 -Wall -Wextra -g -fsanitize=address,undefined -lm

SRCS := main.c attention.c
BIN := attention_test

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRCS) attention.h golden_vectors.h
	$(CC) $(CFLAGS) -o $(BIN) $(SRCS)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)
	rm -rf $(BIN).dSYM
