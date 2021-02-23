#include "rogue.h"

/**
 * Atualiza os stats de uma unidade com o valor de ataque
 * 
 * @param Stats* unit
 * @param Position enemyPosition
 * @param int enemyType
 */
void attack(Stats * unit, Position enemyPosition, int enemyType) {
  int numberOfMonsters = dungeon->levels[dungeon->currentLevel]->numberOfMonsters;
  Monster ** monsters = dungeon->levels[dungeon->currentLevel]->monsters;
  char ** unitsMap = dungeon->levels[dungeon->currentLevel]->unitsMap;

  if (enemyType == MONSTER) {
    for (int i = 0; i < numberOfMonsters; i++) {
      if (monsters[i]->position->x == enemyPosition.x && monsters[i]->position->y == enemyPosition.y) {
        int attackValue = unit->attack - monsters[i]->stats->defence;
        monsters[i]->stats->health -= (attackValue <= 0 ? 0 : attackValue);
        if (monsters[i]->stats->health <= 0) {
          changeUnitsMap(unitsMap, monsters[i]->position, 0, 0, '.');
        }
      }
    }
  }
  else if (enemyType == PLAYER) {
    Stats * playerStats = dungeon->player->stats;
    int attackValue = unit->attack - playerStats->defence;
    playerStats->health -= (attackValue <= 0 ? 0 : attackValue);
  }
}
