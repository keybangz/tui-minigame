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
  int keyPressed;
} gameState;

typedef struct gameWindowContentTag {
  int contentPosY;
  int contentPosX;
  char *content;
} gameWindowContent;

typedef struct gameWindowTag {
  char name[128];
  WINDOW *window;
  int height;
  int width;
  int startY;
  int startX;
  int lifetime;
} gameWindow;

typedef struct gameInterfaceTag {
  int level;
  int type;
  int debug; // 0 is off, 1 is on
  int windowCount;
  gameWindow **gameWindows;
  gameWindowContent **g_winContent;
} gameInterface;

#endif
