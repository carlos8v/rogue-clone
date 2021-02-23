#include "rogue.h"

/**
 * Retorna uma nova instância da struct Player
 *
 * @return Player*
 */
Player * playerSetup() {
  Player * newPlayer = malloc(sizeof(Player));
  newPlayer->position = malloc(sizeof(Position));
  newPlayer->position->x = 15;
  newPlayer->position->y = 15;

  newPlayer->symbol = '@';
  newPlayer->color = ORANGE;

  strcpy(newPlayer->name, "Kovthe");
  strcpy(newPlayer->title, "the Necromancer");

  newPlayer->stats = malloc(sizeof(Stats));
  newPlayer->stats->health = 10;
  newPlayer->stats->maxHealth = 10;
  newPlayer->stats->attack = 10;
  newPlayer->stats->defence = 3;
  newPlayer->stats->vision = 1;
  
  return newPlayer;
}
