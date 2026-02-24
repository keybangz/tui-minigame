#include "mainmenu.h"

void mainMenu(gameInterface *gameInterface) {
  if (!gameInterface)
    return;

  mvprintw(0, 0, "League of Legends TUI Game");
  mvprintw(2, 0, "--- CONTROLS ---");
  mvprintw(4, 0, "BACKSPACE - Exit game.");
}
