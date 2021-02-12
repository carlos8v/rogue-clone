#include "nethack.h"

Player * playerSetup(char ** tiles) {
  Player * newPlayer = malloc(sizeof(Player));
  newPlayer->position.x = 15;
  newPlayer->position.y = 15;

  newPlayer->stats.health = 10;
  newPlayer->stats.attack = 5;
  newPlayer->stats.defence = 5;

  drawUnit(tiles, newPlayer->position, 0, 0, '@');
  
  return newPlayer;
}
