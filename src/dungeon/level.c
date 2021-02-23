#include "rogue.h"

/**
 * Retorna uma nova instância da struct Level
 *
 * @param int level
 * @return Level*
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
 * Checa se a posição está dentro do mapa
 * 
 * @param Position position
 * @param int xOffset
 * @param int yOffset
 * @return bool
 * 
 */
bool outOfBounds(Position position, int xOffset, int yOffset) {
  Position checkPosition;
  checkPosition.x = position.x + xOffset;
  checkPosition.y = position.y + yOffset;
  return (checkPosition.x < 0) || (checkPosition.x > MAP_WIDTH)
    || (checkPosition.y < 0) || (checkPosition.y > MAP_HEIGHT);
}

/**
 * Checa no unitsMap se existe chão, jogador, monstro ou item na posição passada
 * @param Position* position
 * @param int xOffset
 * @param int yOffset
 * @return int
 */
int checkUnits(Position * position, int xOffset, int yOffset) {
  if (outOfBounds(*position, xOffset, yOffset)) return VOID;
  char ** unitsMap = dungeon->levels[dungeon->currentLevel]->unitsMap;
  switch(unitsMap[position->y + yOffset][position->x + xOffset]) {
    case '.': return FLOOR;
    case '@': return PLAYER;
    default: return MONSTER;
  }
}

/**
 * Checa no level atual se a posição passada é caminhável
 *
 * @param Position* position
 * @param int xOffset
 * @param int yOffset
 * @return boolean
 */
bool checkPosition(Position * position, int xOffset, int yOffset) {
  char ** tiles = dungeon->levels[dungeon->currentLevel]->tiles;
  switch (tiles[position->y + yOffset][position->x + xOffset]) {
    case '@': case '%': case '+':
    case '#': case '.':
      return true;
    default:
      return false;
  }
}

/**
 * Retorna um array com todos os caractéres presentes 
 * no level atual, ignorando items ou monstros
 *
 * @return char**
 */
char ** saveTiles() {
  char ** level = malloc(sizeof(char *) * (MAP_HEIGHT + 1));
  for (int j = 0; j <= MAP_HEIGHT; j++) {
    level[j] = malloc(sizeof(char) * (MAP_WIDTH + 1));
    for (int i = 0; i <= MAP_WIDTH; i++) {
      level[j][i] = mvwinch(mapscr, j, i);
    }
  }
  return level;
}

/**
 * Atualiza a informação do UnitsMap
 * 
 * @param char** tiles
 * @param Position* position
 * @param int xOffset
 * @param int yOffset
 * @param char symbol
 */
void changeUnitsMap(char ** unitsMap, Position * position, int xOffset, int yOffset, char symbol) {
  unitsMap[position->y][position->x] = '.';
  unitsMap[position->y + yOffset][position->x + xOffset] = symbol;
}

/**
 * Retorna um array para verificação dos caractéres do personagem e monstros
 *
 * @return char**
 */
char ** initializeUnitsMap() {
  char ** units = malloc(sizeof(char*) * (MAP_HEIGHT + 1));
  for (int j = 0; j <= MAP_HEIGHT; j++) {
    units[j] = malloc(sizeof(char) * (MAP_WIDTH + 1));
    for (int i = 0; i <= MAP_WIDTH; i++) {
      units[j][i] = '.';
    }
  }
  return units;
}
