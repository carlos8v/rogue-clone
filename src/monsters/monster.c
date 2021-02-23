#include "rogue.h"

/**
 * Adiciona os monstros baseado no level passado
 *
 * @param Level* level
 */
void addMonsters(Level * level) {
  int maxMonsters = 6;
  level->monsters = malloc(sizeof(Monster *) * maxMonsters);
  level->numberOfMonsters = 0;
  for (int i = 0; i < level->numberOfRooms; i++) {
    if (level->numberOfMonsters >= maxMonsters) break;
    if ((rand() % 2) == 0) {
      level->monsters[level->numberOfMonsters] = selectMonster(level->level);
      setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[i]);
      changeUnitsMap(level->unitsMap, level->monsters[level->numberOfMonsters]->position,
        0, 0, level->monsters[level->numberOfMonsters]->symbol
      );
      drawUnit(
        level->monsters[level->numberOfMonsters]->position,
        level->monsters[level->numberOfMonsters]->symbol,
        level->monsters[level->numberOfMonsters]->color
      );
      level->numberOfMonsters++;
    }
  }
}

/**
 * Retorna um monsto com a espécie e status baseado no level passado
 *
 * @param int level
 * @return Monster*
 */
Monster * selectMonster(int level) {
  int monsterSpecies;
  switch (level) {
  case 1:
  case 2:
  case 3:
    monsterSpecies = (rand() % 2) + 1;
    break;
  case 4:
  case 5:
    monsterSpecies = (rand() % 2) + 2;
    break;
  case 6:
    monsterSpecies = 3;
    break;
  }

  char monstersNames[3][3][20] = {
    { "Spiders", "Giant Spider", "Scorpion" },
    { "Goblin", "Hobgoblin", "Orc" },
    { "Troll", "Ice Toll", "Water Troll" }
  };
  
  int monstersColors[3][3] = {
    { WHITE, PURPLE, RED },
    { WHITE, ORANGE, RED },
    { ORANGE, WHITE, CYAN }
  };

  int monstersStats[3][3][4] = {
    {
    // HP, Atk, Def, Vision
      { 5, 4, 1, 3 }, // Spider
      { 6, 6, 2, 4 }, // Giant Spider
      { 6, 7, 2, 4 }  // Scorpion
    },
    {
      { 4, 6, 3, 6 }, // Goblin
      { 5, 7, 4, 7 }, // Hobgoblin
      { 6, 8, 4, 8 }  // Orc
    },
    {
      { 15, 9, 4, 7 }, // Troll
      { 15, 9, 4, 7 }, // Ice Troll
      { 15, 9, 4, 8 }  // Water Troll
    }
  };

  int i = rand() % 3;
  switch(monsterSpecies) {
  case 1: // Spider
    return createMonster(
      monstersNames[monsterSpecies - 1][i], 'x', monstersStats[monsterSpecies - 1][i],
      monstersColors[monsterSpecies - 1][i]
    );
  case 2: // Goblin
    return createMonster(
      monstersNames[monsterSpecies - 1][i], 'o', monstersStats[monsterSpecies - 1][i],
      monstersColors[monsterSpecies - 1][i]
    );
  case 3: // Troll
    return createMonster(
      monstersNames[monsterSpecies - 1][i], 'T', monstersStats[monsterSpecies - 1][i],
      monstersColors[monsterSpecies - 1][i]
    );
  }
}

/**
 * Cria e retorna um monstro com as características baseadas nos 
 * parâmetros passados
 *
 * @param char name[20]
 * @param char symbol
 * @param int stats[3]
 * @param int color
 * @return Monster*
 */
Monster * createMonster(char name[20], char symbol, int stats[3], int color) {
  Monster * newMonster = malloc(sizeof(Monster));
  
  strcpy(newMonster->name, name);
  newMonster->symbol = symbol;
  newMonster->color = color;

  newMonster->stats = malloc(sizeof(Stats));
  newMonster->stats->health = stats[0];
  newMonster->stats->maxHealth = stats[0];
  newMonster->stats->attack = stats[1];
  newMonster->stats->defence = stats[2];
  newMonster->stats->vision = stats[3];
  newMonster->seeking = false;

  return newMonster;
}

/**
 * Inicializa uma posição válida para o monstro
 *
 * @param Monster* monster
 * @param Room* room
 */
void setStartingPosition(Monster * monster, Room * room) {
  monster->position = malloc(sizeof(Position));
  monster->position->x = (rand() % (room->width - 2)) + room->position.x + 1;
  monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;
}

/**
 * Move todos os monstros no level atual baseados se estão vagando ou 
 * perseguindo o jogador
 */
void moveMonsters() {
  Player * player = dungeon->player;
  Monster ** monsters = dungeon->levels[dungeon->currentLevel]->monsters;
  char ** unitsMap = dungeon->levels[dungeon->currentLevel]->unitsMap;

  for (int i = 0; i < dungeon->levels[dungeon->currentLevel]->numberOfMonsters; i++) {
    if (monsters[i]->stats->health <= 0) continue;
    monsters[i]->seeking = isInRange(*monsters[i]->position, *player->position, monsters[i]->stats->vision, true, false);

    Position direction;
    if (monsters[i]->seeking)
      direction = seek(monsters[i]->position, player->position);
    else
      direction = wander(monsters[i]->position);

    if (checkUnits(monsters[i]->position, direction.x, direction.y) == FLOOR) {
      changeUnitsMap(unitsMap, monsters[i]->position, direction.x, direction.y, monsters[i]->symbol);
      monsters[i]->position->x += direction.x;
      monsters[i]->position->y += direction.y;
    }
    else if (checkUnits(monsters[i]->position, direction.x, direction.y) == PLAYER) {
      Position enemyPosition;
      enemyPosition.x = monsters[i]->position->x + direction.x;
      enemyPosition.y = monsters[i]->position->y + direction.y;
      attack(monsters[i]->stats, enemyPosition, PLAYER);
    }
  }
}

/**
 * Retorna um offset para a posição do monstro quando ele está vagando
 *
 * @param Position* monsterPosition
 * @return Position* offset
 */
Position wander(Position * monterPosition) {
  Position offset;
  offset.x = (rand() % 3) - 1;
  offset.y = (rand() % 3) - 1;
  if (!checkPosition(monterPosition, offset.x, offset.y)) {
    offset.x = 0;
    offset.y = 0;
  }
  return offset;
}

/**
 * Retorna um offset para a posição do monstro quando ele está perseguindo o jogador
 *
 * @param Position* monsterPosition
 * @param Position* destination
 * @return Position* offset
 */
Position seek(Position * monsterPosition, Position * destination) {
  char ** tiles = dungeon->levels[dungeon->currentLevel]->tiles;
  bool ** rules = malloc(sizeof(bool*) * (MAP_HEIGHT + 1));
  for (int j = 0; j <= MAP_HEIGHT; j++) {
    rules[j] = malloc(sizeof(bool) * (MAP_WIDTH));
    for (int i = 0; i <= MAP_WIDTH; i++) {
      if (tiles[j][i] == '.' || tiles[j][i] == '#' || tiles[j][i] == '+')
        rules[j][i] = true;
      else
        rules[j][i] = false;
    }
  }
  
  Position ** path = getPath(*destination, *monsterPosition, rules);
  Position direction;
  direction.x = path[monsterPosition->y][monsterPosition->x].x - monsterPosition->x;
  direction.y = path[monsterPosition->y][monsterPosition->x].y - monsterPosition->y;
  free(path);
  return direction;
}
