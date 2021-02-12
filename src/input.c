#include "nethack.h"

void handleInput(int input, Player * player, char ** tiles) {
  switch(input) {
    case 'w':
      if (checkPosition(0, -1, player->position)) {
        drawUnit(tiles, player->position, 0, -1, '@');
        player->position.y -= 1;
      }
      break;
    case 'a':
      if (checkPosition(-1, 0, player->position)) {
        drawUnit(tiles, player->position, -1, 0, '@');
        player->position.x -= 1;
      }
      break;
    case 'd':
      if (checkPosition(1, 0, player->position)) {
        drawUnit(tiles, player->position, 1, 0, '@');
        player->position.x += 1;
      }
      break;
    case 's':
      if (checkPosition(0, 1, player->position)) {
        drawUnit(tiles, player->position, 0, 1, '@');
        player->position.y += 1;
      }
      break;
    default:
      break;
  }
  debug(input, player);
}