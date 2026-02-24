#ifndef INITWINDOWS_H
#define INITWINDOWS_H
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct gameWindowTag gameWindow;
typedef struct gameInterfaceTag gameInterface;
typedef struct gameWindowContentTag gameWindowContent;

void initAllWindows(gameInterface *game);

gameWindow *initGameWindow(gameInterface *game, char *title, int height,
                           int width, int offsetPosY, int offsetPosX,
                           int lifetime);

WINDOW *addWindow(gameInterface *game, int height, int width, int startPosY,
                  int startPosX);

void deleteWindow(WINDOW *window);

#endif
