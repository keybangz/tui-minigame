#ifndef INITWINDOWS_H
#define INITWINDOWS_H
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameWindowTag gameWindow;
typedef struct gameInterfaceTag gameInterface;
typedef struct gameWindowContentTag gameWindowContent;

void initAllWindows(gameInterface *);

gameWindow *initGameWindow(gameInterface *, gameWindow *);

WINDOW *addWindow(gameInterface *, int, int, int, int);

void deleteGameWindowContent(gameWindowContent *);
void deleteGameWindow(gameWindow **);

void deleteWindow(WINDOW *);

#endif
