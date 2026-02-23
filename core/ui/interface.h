#ifndef INTERFACE_H
#define INTERFACE_H

#include "../frame/frame.h"
#include "levels/mainmenu.h"

typedef struct terminalWindowTag {
  int x;
  int y;
} terminalWindow;

typedef struct gameInterfaceTag {
  int level;
  int type;
  int debug; // 0 is off, 1 is on
} gameInterface;

// Implement interface functionality
void startDraw(gameInterface *);
void renderUI(gameInterface *, terminalWindow *);

// Debug interface functions
void drawDebugWindow(terminalWindow *);

#endif
