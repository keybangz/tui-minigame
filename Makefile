#   target: dependencies
#       <tab>recipe (the command to run)
#
# - TARGET: The file we want to build (e.g., an executable or an object file).
# - DEPENDENCIES: The files the target needs in order to be built.
# - RECIPE: The command(s) to execute to create the target.
#
# IMPORTANT: The lines with recipes MUST start with a TAB character, not spaces!
PKGS     := ncurses
CC 	 = gcc
CFLAGS   = -Wall -Wextra -std=c11 $(shell pkg-config --cflags $(PKGS))
LDFLAGS  := $(shell pkg-config --libs $(PKGS))
TARGET   = tui_minigame

$(TARGET): main.o frame.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o build/$(TARGET) build/main.o build/frame.o -lncurses

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o build/main.o

frame.o: core/frame.c core/frame.h
	$(CC) $(CFLAGS) -c core/frame.c -o build/frame.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o