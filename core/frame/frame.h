#ifndef FRAME_H
#define FRAME_H

#include <ncurses.h>
#include <time.h>

typedef struct gameStateTag gameState;

void refreshFrame(WINDOW *);
void setupFrame(gameState *);
struct timespec timespec_sub(struct timespec, struct timespec);

#endif
