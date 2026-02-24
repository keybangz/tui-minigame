#include "debugWindow.h"
#include "initWindows.h"

gameWindowContent *addWindowContent(gameWindow *window, char *content, int posY,
                                    int posX) {
  gameWindowContent *g_wincon = *window->g_winContent;

  strcpy(g_wincon->content, content);
  g_wincon->contentPosY = posY;
  g_wincon->contentPosX = posX;

  mvwprintw(window->window, g_wincon->contentPosY, g_wincon->contentPosX, "%s",
            g_wincon->content);

  return g_wincon;
}

void drawWindow(gameInterface *interface, gameWindow *window, char *name,
                int height, int width) {
  window->height = height;
  window->width = width;

  window->startY =
      (interface->screen->x > height) ? (interface->screen->x - -height) : 0;
  window->startX =
      (interface->screen->y > width) ? (interface->screen->y - -width) : 0;

  // window->startY = 0;
  // window->startX = 0;

  strcpy(window->name, name);

  box(window->window, 0, 0);
  wbkgd(window->window, COLOR_PAIR(3));

  window->g_winContent[0] = addWindowContent(window, window->name, 1, 1);
  window->g_winContent[1] = addWindowContent(window, "TEST CONTENT", 2, 1);

  mvwin(window->window, window->startY, window->startX);
  wresize(window->window, window->height, window->width);

  wrefresh(window->window);
  wclear(window->window);
}

void drawDebugWindow(gameInterface *interface, gameWindow *window) {
  strcpy(window->name, "Debug Window");
  window->width = 30;
  window->height = 10;

  box(window->window, 0, 0);
  wbkgd(window->window, COLOR_PAIR(3));

  window->g_winContent[1] = addWindowContent(window, "Test Debug Window", 1, 1);

  char buff[512];
  static int count = 0;
  sprintf(buff, "Count %d", count);
  count++;

  window->g_winContent[2] = addWindowContent(window, buff, 2, 1);

  int offsetY = (interface->screen->y > window->height
                     ? (interface->screen->y - window->height)
                     : 0);

  int offsetX = (interface->screen->x > window->width
                     ? (interface->screen->x - window->width)
                     : 0);

  mvwin(window->window, offsetY, offsetX);
  wresize(window->window, window->height, window->width);

  wrefresh(window->window);
  wclear(window->window);
}
