#include "interface.h"

/*
 * I will need to scaffold this section out from defining what parts of the UI
 * is rendered on what function, What helper functions will be included from the
 * ./helper directory for setting attributes for colors used, setting text type,
 * text updates and what needs to be returned too and from the UI for specific
 * mechanical parts of the game.
 */

void draw_ui(void) {
  clear(); // Clear virtual screen

  // 0,0 is top left corner of screen
  mvprintw(0, 0, "Test print on interface environment");

  // attron - Turn attribute on
  attron(COLOR_PAIR(1) |
         A_BOLD); // Turn the pair defined in init() and make text bold.
  mvprintw(2, 2, "Test yellow bold text on black bg");
  attroff(COLOR_PAIR(1) | A_BOLD); // attroff, turn selected attributes off.

  mvprintw(4, 2, "Standard text again.");

  refreshFrame(NULL); // Wrapper function for refresh() & wrefresh()

  // Refactor later.
  int height = 10, width = 60;
  int start_y = 6, start_x = 5;

  // newwin creates a window inside the virtual screen
  WINDOW *info_win = newwin(height, width, start_y, start_x);

  // Draw border around the window
  box(info_win, 0, 0);

  // Attribute for window color only
  wbkgd(info_win, COLOR_PAIR(3));

  // mvwprintw is the window specific function of mvprintw
  // Coordinates are relative to top left of new window, just like virtual
  // screen.
  mvwprintw(info_win, 1, 1, "New window test.");

  // Modular refreshment of window only.
  refreshFrame(info_win);
}
