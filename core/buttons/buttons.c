#include "buttons.h"
#include "../game.h"

int mapKeyPress(gameState *state) {
  if (!state)
    return -1;

  return state->keyPressed;
}

void mapActionToKey(gameState *state) {
  if (!state)
    return;
}
