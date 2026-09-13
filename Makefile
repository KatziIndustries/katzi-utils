CC := gcc
CFLAGS := -Wall -Wextra -O2

PROGRAMS := $(notdir $(wildcard src/*))

all: $(PROGRAMS:%=bin/%)

bin:
	mkdir -p bin

bin/%: src/%/main.c | bin
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf bin
	