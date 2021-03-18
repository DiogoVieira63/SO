CC = gcc
PROG = programa
CFLAGS = -g -std=gnu11 -Wall -Wextra -pedantic-errors -O
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))



$(PROG): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	@$(CC) $(CFLAGS) -c $^

.PHONY: build
build: $(PROG)

.PHONY: run
run: $(PROG)
	@./$(PROG)

.PHONY : clean
clean: 
	-@rm *.o $(PROG)