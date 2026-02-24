#include "initWindows.h"
#include "../game.h"
#include <ncurses.h>

void initAllWindows(gameInterface *game) {
  if (!game)
    return;

  game->gameWindows = malloc(7 * sizeof(gameWindow *));

  if (!game->gameWindows)
    return;

  for (int i = 0; i < 1; i++) {
    game->gameWindows[i] = malloc(sizeof(gameWindow));
    if (!game->gameWindows[i])
      return;

    game->gameWindows[i]->g_winContent =
        malloc(3 * sizeof(gameWindowContent *));

    if (!game->gameWindows[i]->g_winContent)
      return;

    for (int j = 0; j < 3; j++) {
      game->gameWindows[i]->g_winContent[j] = malloc(sizeof(gameWindowContent));

      if (!game->gameWindows[i]->g_winContent[j])
        return;

      game->gameWindows[i] = initGameWindow(
          game, game->gameWindows[i]->name, game->gameWindows[i]->height,
          game->gameWindows[i]->width, game->gameWindows[i]->startX,
          game->gameWindows[i]->startX, game->gameWindows[i]->lifetime,
          game->gameWindows[i]->g_winContent);
    }
  }
}

gameWindow *initGameWindow(gameInterface *game, char *title, int height,
                           int width, int offsetPosY, int offsetPosX,
                           int lifetime, gameWindowContent **content) {

  gameWindow *g_win = (gameWindow *)malloc(sizeof(gameWindow));

  int maxY = game->screen->x;
  int maxX = game->screen->y;

  g_win->width = width;
  g_win->height = height;
  g_win->startY =
      (maxY > height) ? (maxY - height) - offsetPosY : 0 - offsetPosY;
  g_win->startX = (maxX > width) ? (maxX - width) - offsetPosX : 0 - offsetPosX;

  g_win->window = addWindow(game, height, width, g_win->startY, g_win->startX);

  strcpy(g_win->name, title);
  g_win->lifetime = lifetime;

  g_win->g_winContent = content;

  game->windowCount++;

  return g_win;
}

void deleteGameWindow(gameWindow *window) {
  for (int i = 0; i < 3; i++) {
    deleteGameWindowContent(window->g_winContent[i]);
  }

  deleteWindow(window->window);
  free(window);
}

void deleteGameWindowContent(gameWindowContent *content) { free(content); }

WINDOW *addWindow(gameInterface *game, int height, int width, int startPosY,
                  int startPosX) {
  if (!game)
    return NULL;

  WINDOW *newWin = newwin(startPosY, startPosX, width, height);

  wrefresh(newWin);

  return newWin;
}

void deleteWindow(WINDOW *window) {
  wclear(window);
  wrefresh(window);
  delwin(window);
}
