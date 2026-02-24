#ifndef DEBUG_WINDOW_H
#define DEBUG_WINDOW_H

#include "../game.h"
#include <stdlib.h>
#include <string.h>

typedef struct gameInterfaceTag gameInterface;
typedef struct gameWindowTag gameWindow;

gameWindowContent *addWindowContent(gameWindow *, char *, int, int);
void drawDebugWindow(gameInterface *, gameWindow *);

#endif
