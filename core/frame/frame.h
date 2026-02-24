#ifndef FRAME_H
#define FRAME_H

#include <ncurses.h>
#include <time.h>

typedef struct gameStateTag gameState;
typedef struct gameInterfaceTag gameInterface;
typedef struct gameWindowTag gameWindow;

void refreshFrame(WINDOW *);
void setupFrame(gameState *, gameInterface *);
struct timespec timespec_sub(struct timespec, struct timespec);

#endif
