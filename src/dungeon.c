#include "nethack.h"

Dungeon * dungeonSetup() {
  Dungeon * newDungeon = malloc(sizeof(Dungeon));
  newDungeon->currentLevel = 1;
  newDungeon->numberOfLevels = 6;
  newDungeon->player = playerSetup();

  newDungeon->levels = malloc(sizeof(Level *) * newDungeon->numberOfLevels);
  for (int i = 0; i < newDungeon->numberOfLevels; i++) {
    clear();
    newDungeon->levels[i] = createLevel(i + 1);
  }

  return newDungeon;
}
