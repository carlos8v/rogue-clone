#include "nethack.h"

/**
 * Retorna uma nova instância da struct Level
 *
 * @param int level
 * @returns Level*
 */
Level * createLevel(int level) {
  Level *  newLevel = malloc(sizeof(Level));
  newLevel->level = level;
  newLevel->numberOfRooms = 3;
  newLevel->rooms = roomsSetup();
  newLevel->tiles = saveTiles();
  newLevel->unitsMap = initializeUnitsMap();
  addMonsters(newLevel);
  return newLevel;
}

/**
 * Checa no unitsMap se existe chão, jogador, monstro ou item na posição passada
 * @param Level* level
 * @param Position* position
 * @param Position offset
 * @returns int
 */
int checkUnits(Level * level, Position * position, Position offset) {
  if (level->unitsMap[position->y + offset.y][position->x + offset.x] == '.') return FLOOR;
  return MONSTER;
}

/**
 * Checa no level atual se a posição passada é caminhável
 *
 * @param Position* position
 * @param int xOffset
 * @param int yOffset
 * @returns boolean
 */
bool checkPosition(Position * position, int xOffset, int yOffset) {
  char target;
  switch (target = mvinch(position->y + yOffset, position->x + xOffset)) {
    case '%':
    case '+':
    case '#':
    case '.':
      return true;
    default:
      return false;
  }
}

/**
 * Retorna um array com todos os caractéres presentes 
 * no level atual, ignorando items ou monstros
 *
 * @returns char**
 */
char ** saveTiles() {
  char ** level = malloc(sizeof(char *) * (SCREEN_HEIGHT + 1));
  for (int j = 0; j <= SCREEN_HEIGHT; j++) {
    level[j] = malloc(sizeof(char) * (SCREEN_WIDTH + 1));
    for (int i = 0; i <= SCREEN_WIDTH; i++) {
      level[j][i] = mvinch(j, i);
    }
  }
  return level;
}

/**
 * Atualiza a informação do UnitsMap
 * @param Level* level
 * @param Position* position
 * @param int xOffset
 * @param int yOffset
 * @param char symbol
 */
void changeUnitsMap(Level * level, Position * position, int xOffset, int yOffset, char symbol) {
  level->unitsMap[position->y][position->x] = '.';
  level->unitsMap[position->y + yOffset][position->x + xOffset] = symbol;
}

/**
 * Retorna um array para verificação dos caractéres do personagem e monstros
 *
 * @returns char**
 */
char ** initializeUnitsMap() {
  char ** units = malloc(sizeof(char*) * (SCREEN_HEIGHT + 1));
  for (int j = 0; j <= SCREEN_HEIGHT; j++) {
    units[j] = malloc(sizeof(char) * (SCREEN_WIDTH + 1));
    for (int i = 0; i <= SCREEN_WIDTH; i++) {
      units[j][i] = '.';
    }
  }
  return units;
}
