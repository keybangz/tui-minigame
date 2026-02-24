#include "initWindows.h"
#include "../game.h"
#include <ncurses.h>

void initAllWindows(gameInterface *game) {
  if (!game)
    return;

  game->gameWindows = malloc(7 * sizeof(gameWindow *));

  if (!game->gameWindows)
    return;

  for (int i = MAINMENU; i <= DEBUG; i++) {
    game->gameWindows[i] = realloc(game->gameWindows[i], sizeof(gameWindow));
    if (!game->gameWindows[i])
      break;

    game->gameWindows[i]->g_winContent =
        malloc(20 * sizeof(gameWindowContent *));

    if (!game->gameWindows[i]->g_winContent)
      break;

    for (int j = 0; j < 20; j++) {
      game->gameWindows[i]->g_winContent[j] = realloc(
          game->gameWindows[i]->g_winContent[j], sizeof(gameWindowContent));

      if (!game->gameWindows[i]->g_winContent[j])
        break;

      game->gameWindows[i] = initGameWindow(game, game->gameWindows[i]);
    }
  }
}

gameWindow *setupWindow(gameInterface *game, char *title, int height, int width,
                        int offsetPosY, int offsetPosX, int lifetime,
                        gameWindowContent **content) {
  gameWindow *g_win = (gameWindow *)malloc(sizeof(gameWindow));

  int maxY = game->screen->x;
  int maxX = game->screen->y;

  g_win->width = 10;
  g_win->height = 10;
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

gameWindow *initGameWindow(gameInterface *interface, gameWindow *window) {
  window = setupWindow(interface, window->name, window->height, window->width,
                       window->startY, window->startX, window->lifetime,
                       window->g_winContent);

  return window;
}

void deleteGameWindow(gameWindow **window) {
  for (int i = MAINMENU; i <= DEBUG; i++) {

    for (int j = 0; j > 20; j++)
      deleteGameWindowContent(window[i]->g_winContent[j]);

    free(window[i]->g_winContent);
    deleteWindow(window[i]->window);
    free(window[i]);
  }
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
