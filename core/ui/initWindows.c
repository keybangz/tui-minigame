#include "initWindows.h"
#include "../game.h"
#include <ncurses.h>

void initAllWindows(gameInterface *game) {
  if (!game)
    return;

  game->gameWindows = malloc(7 * sizeof(gameWindow *));

  for (int i = 0; i < game->windowCount; i++) {
    game->gameWindows[i] = malloc(sizeof(gameWindow));

    // game->gameWindows[i] = initGameWindow(
    //     game, game->gameWindows[i]->name, game->gameWindows[i]->height,
    //     game->gameWindows[i]->width, game->gameWindows[i]->startX,
    //     game->gameWindows[i]->startX, game->gameWindows[i]->lifetime);
  }
}

gameWindow *initGameWindow(gameInterface *game, char *title, int height,
                           int width, int offsetPosY, int offsetPosX,
                           int lifetime) {

  gameWindow *g_win = (gameWindow *)malloc(sizeof(gameWindow));

  int maxY = getmaxy(stdscr);
  int maxX = getmaxx(stdscr);

  g_win->width = width;
  g_win->height = height;
  g_win->startY =
      (maxY > height) ? (maxY - height) + offsetPosY : 0 + offsetPosY;
  g_win->startX = (maxX > width) ? (maxX - width) + offsetPosX : 0 + offsetPosX;

  g_win->window = addWindow(game, height, width, g_win->startY, g_win->startX);

  strcpy(g_win->name, title);
  g_win->lifetime = lifetime;

  return g_win;
}

WINDOW *addWindow(gameInterface *game, int height, int width, int startPosY,
                  int startPosX) {
  if (!game)
    return NULL;

  int maxY = getmaxy(stdscr);
  int maxX = getmaxx(stdscr);

  startPosY = (maxY > height) ? (maxY - height) : 0;
  startPosX = (maxX > width) ? (maxX - width) : 0;

  WINDOW *newWin = newwin(startPosY, startPosX, width, height);

  wrefresh(newWin);

  return newWin;
}

void deleteWindow(WINDOW *window) {
  wclear(window);
  wrefresh(window);
  delwin(window);
}
