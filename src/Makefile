
NAME = fml

BINDIR = ./..

# unixy
NAT_BIN = $(BINDIR)/$(NAME)
NAT_CC = gcc

# tos
TOS_BIN = $(BINDIR)/$(NAME).tos
TOS_CC = m68k-atari-mint-gcc
TOS_SP = m68k-atari-mint-strip
TOS_CFLAGS = -Os -m68000 -std=c99 -fomit-frame-pointer -Wall

DEPS = main.c Makefile

.PHONY: clean

native : main.c $(DEPS)
	$(CC) -o $(NAT_BIN) main.c

tos : main.c $(DEPS)
	$(TOS_CC) $(TOS_CFLAGS) -c main.c -o main_tos.o
	$(TOS_CC) $(TOS_CFLAGS) -o $(TOS_BIN) main_tos.o -lgcc
	$(TOS_SP) -s -x $(TOS_BIN)

all : native tos

clean:
	rm -f $(NAT_BIN) $(TOS_BIN) *.o
