#include "nethack.h"

/**
 * Retorna uma nova instância da struct Dungeon
 *
 * @returns Dungeon*
 */
Dungeon * dungeonSetup() {
  Dungeon * newDungeon = malloc(sizeof(Dungeon));
  newDungeon->currentLevel = 0;
  newDungeon->numberOfLevels = 6;
  newDungeon->player = playerSetup();

  newDungeon->levels = malloc(sizeof(Level *) * newDungeon->numberOfLevels);
  for (int i = 0; i < newDungeon->numberOfLevels; i++) {
    wclear(mapscr);
    newDungeon->levels[i] = createLevel(i + 1);
  }

  changeUnitsMap(newDungeon->levels[0]->unitsMap, newDungeon->player->position, 0, 0, newDungeon->player->symbol);

  return newDungeon;
}
