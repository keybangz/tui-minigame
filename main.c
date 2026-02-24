#include "core/game.h"

#include <ncurses.h> // For TUI framework ncurses
#include <stdint.h>
#include <stdio.h>
#include <unistd.h> // For sleep

/*
 * NCurses TUI Game
 * Goal: Create simple League of Legends like laning phase mini-game
 *
 * TODO:
 *    - Refactor current code outside of main file.
 *    - Add functionality in different files e.g. control binding, UI control,
 *    framerate control, main core loop control
 *    - Create UI framework helper functions for drawing different sized windows
 *    for different usages on screen (main menu, in-game, etc)
 *    - Add mouse input
 *
 *    - Thanks to https://github.com/dunamismax/c-from-the-ground-up for simple
 *    implementation demonstration of ncurses.
 */

// Memory management
void init(void);
void cleanup(void);

int main(int argc, char *argv[]) {
  if (argc > 1) {
    printf("Usage: %s\n", argv[0]);
    return 1;
  }

  gameState state;
  gameInterface interface;

  interface.windowCount = 0;

  init(); // Initialize ncurses

  startDraw(&interface); // Initialize interface state

  state.running = 1;              // Toggle game state
  setupFrame(&state, &interface); // Setup frame rendering

  cleanup(); // Cleanup memory from ncurses
  return 0;
}

/*
- Ncurses core functions
*/
void init(void) {
  initscr(); // NCurses initialize screen function.
  noecho();  // Prevents keypresses being instantly displayed on screen.
  cbreak();  // Makes input available to terminal without use of ENTER

  keypad(stdscr, TRUE); // Enable input of arrow keys, F1,F2 etc

  // Initialize colors, if terminal does not support colors, exit.
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support colors, game ending...\n");
  }

  // Start NCurses coloring system.
  start_color();

  // Colors pairs, yellow text on black bg
  // Cyan on black bg
  // White on blue bg
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_WHITE, COLOR_BLUE);
}

void cleanup(void) { endwin(); }
