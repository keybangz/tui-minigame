#include "frame.h"
#include "../game.h"
#include "../ui/interface.h"

void setupFrame(gameState *state, gameInterface *interface) {
  if (!state)
    return;

  // REF: https://www.altdevarts.com/p/a-simple-main-game-loop-with-ncurses
  struct timespec frame_time;
  struct timespec remaining_time;
  struct timespec target_time = {0, 16666666};

  while (state->running) {
    struct timespec start_time;
    clock_gettime(CLOCK_REALTIME, &start_time);
    // --- START OF FRAME ABOVE ---

    renderUI(interface);

    // --- END OF FRAME BELOW ---
    struct timespec end_time;
    clock_gettime(CLOCK_REALTIME, &end_time);

    frame_time = timespec_sub(start_time, end_time);
    remaining_time = timespec_sub(frame_time, target_time);

    nanosleep(&remaining_time, NULL);

    timeout(0);
    state->keyPressed = getch();

    if (!state->running || state->keyPressed == KEY_BACKSPACE) {
      state->running = 0;
      break;
    }
  }
}

void refreshFrame(WINDOW *window) {
  if (window) {
    wrefresh(window);
  } else
    refresh();
}

// REF: https://www.altdevarts.com/p/a-simple-main-game-loop-with-ncurses
// https://sourceware.org/glibc/manual/2.34/html_node/Calculating-Elapsed-Time.html
struct timespec timespec_sub(struct timespec start, struct timespec end) {
  struct timespec temp;

  if ((end.tv_nsec - start.tv_nsec) < 0) {
    temp.tv_sec = end.tv_sec - start.tv_sec - 1;
    temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec - start.tv_sec;
    temp.tv_nsec = end.tv_nsec - start.tv_nsec;
  }

  return temp;
}
