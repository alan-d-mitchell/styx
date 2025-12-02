CC = clang
CFLAGS = -Wall -Wextra -g
TARGET = styx

SRC_DIR = src
BIN_DIR = bin

SRC = $(SRC_DIR)/styx.c $(SRC_DIR)/mkrepo.c $(SRC_DIR)/add.c
OBJ = $(SRC:.c=.o)

build: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJ)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(BIN_DIR)/$(TARGET)

