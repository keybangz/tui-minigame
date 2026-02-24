#include "interface.h"
#include "../game.h"
#include "debugWindow.h"
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

  gameInterface->screen->x = getmaxx(stdscr);
  gameInterface->screen->y = getmaxy(stdscr);

  if (gameInterface->type == MAINMENU) {
    drawWindow(gameInterface, gameInterface->gameWindows[MAINMENU], "Main Menu",
               10, 50);
  }

  if (gameInterface->debug)
    drawDebugWindow(gameInterface, gameInterface->gameWindows[DEBUG]);

  refreshFrame(NULL); // Refresh virtual screen to show drawn items.

  clear(); // Clear virtual screen at end of frame to ensure old frames drawn do
           // not show.
}
