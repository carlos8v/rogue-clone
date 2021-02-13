#include "nethack.h"

/**
 * Retorna uma nova instância da struct Player
 *
 * @returns Player
 */
Player * playerSetup() {
  Player * newPlayer = malloc(sizeof(Player));
  newPlayer->position = malloc(sizeof(Position));
  newPlayer->position->x = 15;
  newPlayer->position->y = 15;

  newPlayer->symbol = '@';
  newPlayer->color = 6;

  newPlayer->stats.health = 10;
  newPlayer->stats.attack = 5;
  newPlayer->stats.defence = 5;
  
  return newPlayer;
}
