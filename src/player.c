#include "nethack.h"

Player * playerSetup(char ** tiles) {
  Player * newPlayer = malloc(sizeof(Player));
  newPlayer->position.x = 15;
  newPlayer->position.y = 15;
  newPlayer->health = 10;

  drawUnit(tiles, newPlayer->position, 0, 0, '@');
  
  return newPlayer;
}
