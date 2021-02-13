#include "nethack.h"

Player * playerSetup(char ** tiles) {
  Player * newPlayer = malloc(sizeof(Player));
  newPlayer->position = malloc(sizeof(Position));
  newPlayer->position->x = 15;
  newPlayer->position->y = 15;

  newPlayer->symbol = '@';
  newPlayer->color = 6;

  newPlayer->stats.health = 10;
  newPlayer->stats.attack = 5;
  newPlayer->stats.defence = 5;

  drawUnit(tiles, newPlayer->position, 0, 0, newPlayer->symbol, newPlayer->color);
  move(newPlayer->position->y, newPlayer->position->x);
  
  return newPlayer;
}
