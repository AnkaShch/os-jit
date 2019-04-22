CC = gcc
CFLAGS = -std=gnu99
SRCS = jit.c
OBJS = $(SRCS: .c = .o)
PROG = jit

all: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(PROG)

run: all
	./$(PROG)

clean:
	rm *.o

