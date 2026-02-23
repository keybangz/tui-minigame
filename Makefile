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

$(shell mkdir -p build)

$(TARGET): main.o frame.o interface.o
	$(CC) $(CFLAGS) -o build/$(TARGET) build/main.o build/frame.o build/interface.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o build/main.o

frame.o: core/frame/frame.h core/frame/frame.c
	$(CC) $(CFLAGS) -c core/frame/frame.c -o build/frame.o

interface.o: core/ui/interface.c core/ui/interface.h
	$(CC) $(CFLAGS) -c core/ui/interface.c -o build/interface.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o
