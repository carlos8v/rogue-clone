#include "nethack.h"

/**
 * Retorna uma nova instância da struct Level
 *
 * @param int level
 * @returns Level
 */
Level * createLevel(int level) {
  Level *  newLevel = malloc(sizeof(Level));
  newLevel->level = level;
  newLevel->numberOfRooms = 3;
  newLevel->rooms = roomsSetup();
  newLevel->tiles = saveLevelPositions();
  addMonsters(newLevel);
  return newLevel;
}

/**
 * Checa no level atual se a posição passada é caminhável
 *
 * @param int xOffset
 * @param int yOfsset
 * @param *Position position
 * @returns boolean
 */
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

/**
 * Retorna um array com todos os caractéries presentes 
 * no level atual, ignorando items ou monstros
 *
 * @returns **char
 */
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
