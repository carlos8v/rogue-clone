#include "nethack.h"

void attack(Level * level, Stats * unit, Position enemyPosition, int enemyType) {
  if (enemyType == MONSTER) {
    for (int i = 0; i < level->numberOfMonsters; i++) {
      if (level->monsters[i]->position->x == enemyPosition.x && level->monsters[i]->position->y == enemyPosition.y) {
        level->monsters[i]->stats->health -= (unit->attack - level->monsters[i]->stats->defence);
        if (level->monsters[i]->stats->health <= 0) {
          changeUnitsMap(level, level->monsters[i]->position, 0, 0, '.');
        }
      }
    }
  }
}