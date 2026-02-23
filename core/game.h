#ifndef GAME_H
#define GAME_H

#include <ncurses.h> // For TUI framework ncurses
#include <stdint.h>
#include <time.h>
#include <unistd.h> // For sleep

#include "buttons/buttons.h"
#include "frame/frame.h"
#include "ui/interface.h"

// TODO: Refactor globals?

typedef struct gameStateTag {
  int running;
  int testCount;
  int keyPressed;
} gameState;

#endif
