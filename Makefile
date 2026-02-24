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

$(TARGET): main.o frame.o interface.o levels.o initWindows.o
	$(CC) $(CFLAGS) -o build/$(TARGET) build/main.o build/frame.o build/interface.o build/levels.o build/initWindows.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o build/main.o

frame.o: core/frame/frame.h core/frame/frame.c
	$(CC) $(CFLAGS) -c core/frame/frame.c -o build/frame.o

interface.o: core/ui/interface.h core/ui/interface.c
	$(CC) $(CFLAGS) -c core/ui/interface.c -o build/interface.o

initWindows.o: core/ui/initWindows.h core/ui/initWindows.c
	$(CC) $(CFLAGS) -c core/ui/initWindows.c -o build/initWindows.o

levels.o: core/ui/levels/mainmenu.h core/ui/levels/mainmenu.c
	$(CC) $(CFLAGS) -c core/ui/levels/mainmenu.c -o build/levels.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o
