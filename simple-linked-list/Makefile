# Simple Makefile — compiles all .c files in this directory into one executable
TARGET := main-simple-linked-list

CC := gcc
CFLAGS := -Wall -Wextra -O2
LDFLAGS :=

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)
