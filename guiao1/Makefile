CC = gcc
CFLAGS = -g -std=gnu11 -Wall -Wextra -pedantic-errors -O
#SRCS = $(wildcard *.c) $(wildcard */*.c)

SRCS = pessoas.c read_ln.c

OBJS = $(SRCS:.c=.o)
MAIN = pessoas


all:    $(MAIN)  
	@echo "Main compiled"
		@ rm $(OBJS)

$(MAIN): $(OBJS) 
	@ $(CC) $(CFLAGS) -o $(MAIN) $(OBJS) -lm

.c.o:
	@ $(CC) $(CFLAGS) -c $<  -o $@