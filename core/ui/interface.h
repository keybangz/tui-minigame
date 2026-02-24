#ifndef INTERFACE_H
#define INTERFACE_H

#include "../frame/frame.h"
#include "levels/mainmenu.h"

typedef struct terminalWindowTag {
  int x;
  int y;
} terminalWindow;

// Implement interface functionality
void startDraw(gameInterface *);
void renderUI(gameInterface *);

// Debug interface functions
void drawDebugWindow(gameWindow *window);

#endif
