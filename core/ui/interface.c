#include "interface.h"
#include <ncurses.h>

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

  clear();

  gameInterface->level = 0;
  gameInterface->type = 0;
  gameInterface->debug = 1;
}

// This function needs to be refactored to take into consideration interface
// type & level too ensure we are rendering the correct things on the screen.
void renderUI(gameInterface *gameInterface, terminalWindow *terminal) {
  if (!gameInterface)
    return;

  terminal->x = getmaxx(stdscr);
  terminal->y = getmaxy(stdscr);

  if (gameInterface->debug) {
    drawDebugWindow(terminal);
  }

  if (gameInterface->type == 0) {
    mainMenu(gameInterface);
  }
}

void drawDebugWindow(terminalWindow *terminal) {
  int height = 10, width = 30;
  int start_y = (terminal->y / 10), start_x = (terminal->x / 10);

  WINDOW *info_win = newwin(height, width, start_y, start_x);

  box(info_win, 0, 0);
  wbkgd(info_win, COLOR_PAIR(3));

  static int count = 0;
  mvwprintw(info_win, 1, 1, "Count: %d", count);
  mvwprintw(info_win, 2, 1, "t_height: %d", terminal->y);
  mvwprintw(info_win, 4, 1, "t_width: %d", terminal->x);
  count++;

  erase();
  refreshFrame(info_win);
}
