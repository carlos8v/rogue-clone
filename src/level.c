#include "nethack.h"

Level * createLevel(int level) {
  Level *  newLevel = malloc(sizeof(Level));
  newLevel->level = level;
  newLevel->numberOfRooms = 3;
  newLevel->rooms = roomsSetup();
  newLevel->tiles = saveLevelPositions();
  addMonsters(newLevel);
  return newLevel;
}

bool checkPosition(int xOffset, int yOffset, Position * position) {
  char target;
  switch (target = mvinch(position->y + yOffset, position->x + xOffset)) {
    case '+':
    case '#':
    case '.':
      return true;
    default:
      return false;
  }
}

char ** saveLevelPositions() {
  char ** level = malloc(sizeof(char *) * 30);
  for (int j = 0; j < 30; j++) {
    level[j] = malloc(sizeof(char) * 100);
    for (int i = 0; i < 100; i++) {
      level[j][i] = mvinch(j, i);
    }
  }
  return level;
}
