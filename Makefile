CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = scheduler.c
OBJ_DIR = obj
OBJ = $(OBJ_DIR)/scheduler.o
TARGET = scheduler

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ): $(SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)