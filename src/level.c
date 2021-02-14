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
 * @param *Position position
 * @param int xOffset
 * @param int yOfsset
 * @returns boolean
 */
bool checkPosition(Position * position, int xOffset, int yOffset) {
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
  char ** level = malloc(sizeof(char *) * (SCREEN_HEIGHT + 1));
  for (int j = 0; j <= SCREEN_HEIGHT; j++) {
    level[j] = malloc(sizeof(char) * (SCREEN_WIDTH + 1));
    for (int i = 0; i <= SCREEN_WIDTH; i++) {
      level[j][i] = mvinch(j, i);
    }
  }
  return level;
}
