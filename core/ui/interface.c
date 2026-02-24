#include "interface.h"
#include "../game.h"
#include "initWindows.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>

/*
 * I will need to scaffold this section out from defining what parts of the UI
 * is rendered on what function, What helper functions will be included from the
 * ./helper directory for setting attributes for colors used, setting text type,
 * text updates and what needs to be returned too and from the UI for specific
 * mechanical parts of the game.
 */
// TODO: Refactor startDraw to initialize concepts of different windows,
// (creation, destruction, clear, etc) At the moment, renderUI is looping within
// every frame, which unnecessarily allocates more memory than it should, and
// also creates undesired effects when windows update to the size of the virtual
// screen.
void startDraw(gameInterface *gameInterface) {
  if (!gameInterface) {
    fprintf(stderr, "gameInterfaces failed to initialize! exiting...\n");
    return;
  }

  gameInterface->level = 0;
  gameInterface->type = 0;
  gameInterface->debug = 1;

  initAllWindows(gameInterface);
}

// This function needs to be refactored to take into consideration interface
// type & level too ensure we are rendering the correct things on the screen.
void renderUI(gameInterface *gameInterface) {
  if (!gameInterface)
    return;

  if (gameInterface->type == 0) {
    mainMenu(gameInterface);
  }

  refreshFrame(NULL); // Refresh virtual screen to show drawn items.

  clear(); // Clear virtual screen at end of frame to ensure old frames drawn do
           // not show.
}

void drawDebugWindow(gameWindow *window) {
  int maxY = getmaxy(stdscr);
  int maxX = getmaxx(stdscr);
  window->startY = (maxY > window->height) ? (maxY - window->height) : 0;
  window->startX = (maxX > window->width) ? (maxX - window->width) : 0;

  mvwin(window->window, window->startY, window->startX);
  wresize(window->window, window->height, window->width);

  box(window->window, 0, 0);
  wbkgd(window->window, COLOR_PAIR(3));

  static int count = 0;
  mvwprintw(window->window, 0, 0, "%s", window->name);
  mvwprintw(window->window, 1, 1, "Count: %d", count);
  mvwprintw(window->window, 2, 1, "posX: %d", window->startY);
  mvwprintw(window->window, 3, 1, "posY: %d", window->startX);
  count++;

  refreshFrame(window->window);

  wclear(window->window);
}
