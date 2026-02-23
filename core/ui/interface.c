#include "interface.h"
#include <ncurses.h>

/*
 * I will need to scaffold this section out from defining what parts of the UI
 * is rendered on what function, What helper functions will be included from the
 * ./helper directory for setting attributes for colors used, setting text type,
 * text updates and what needs to be returned too and from the UI for specific
 * mechanical parts of the game.
 */

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

  if (gameInterface->debug)
    drawDebugWindow(terminal->y, terminal->x);

  if (gameInterface->type == 0) {
    mainMenu(gameInterface);
  }
}

void drawDebugWindow(int t_height, int t_width) {
  int height = 9, width = 24;
  int start_y = 40, start_x = 1;

  WINDOW *info_win = newwin(height, width, start_y, start_x);

  box(info_win, 0, 0);
  wbkgd(info_win, COLOR_PAIR(3));

  int count = debugThinkCount();
  mvwprintw(info_win, 1, 1, "Count: %d", count);
  mvwprintw(info_win, 2, 1, "t_height: %d", t_height);
  mvwprintw(info_win, 4, 1, "t_width: %d", t_width);

  refreshFrame(info_win);
}

int debugThinkCount() {
  static int count = 0;
  return count++;
}
