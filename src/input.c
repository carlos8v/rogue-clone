#include "nethack.h"

/*
Commands:
  7   8   9
   \  |  /
  4 — 5 — 6     - Moviment
   /  |  \
  1   2   3

  w, a, s, d    - 4-Direction Moviment
  .             - Do nothing;

*/

bool handleInput(int input, Player * player, char ** tiles) {
  int xOffset = 0;
  int yOffset = 0;
  bool shouldMove = false;
  switch(input) {
    case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9': case 'w':
    case 'a': case 's': case 'd':
      if (input == 'w' || input == '8') yOffset = -1;
      else if (input == 'a' || input == '4') xOffset = -1;
      else if (input == 's' || input == '2') yOffset = 1;
      else if (input == 'd' || input == '6') xOffset = 1;
      else if (input == '1') { xOffset = -1; yOffset = 1; }
      else if (input == '3') { xOffset = 1; yOffset = 1; }
      else if (input == '7') { xOffset = -1; yOffset = -1; }
      else if (input == '9') { xOffset = 1; yOffset = -1; }
      if (checkPosition(xOffset, yOffset, player->position)) {
        drawUnit(tiles, player->position, xOffset, yOffset, player->symbol);
        player->position->x += xOffset;
        player->position->y += yOffset;
        shouldMove = true;
      }
      break;
    case '.':
      shouldMove = true;
      break;
    default:
      mvprintw(38, 0, "Comando não encontrado");
      break;
  }
  debug(input, player);
  return shouldMove;
}