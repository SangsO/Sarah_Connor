# Simple Makefile — builds two separate executables
TARGET1 := main-simple-linked-list
TARGET2 := main-simple-linked-list-2

CC := gcc
CFLAGS := -Wall -Wextra -O2
LDFLAGS :=

# Common object file
COMMON_OBJ := linked-list.o

# All object files (for cleanup)
OBJS := linked-list.o main.o main_2.o

.PHONY: all clean run run2

all: $(TARGET1) $(TARGET2)

$(TARGET1): main.o $(COMMON_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(TARGET2): main_2.o $(COMMON_OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJS)

run: $(TARGET1)
	./$(TARGET1)

run2: $(TARGET2)
	./$(TARGET2)
