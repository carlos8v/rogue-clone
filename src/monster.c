#include "nethack.h"

void addMonsters(Level * level) {
  level->monsters = malloc(sizeof(Monster *) * 6);
  level->numberOfMonsters = 0;

  for (int i = 0; i < level->numberOfRooms; i++) {
    if ((rand() % 2) == 0) {
      level->monsters[level->numberOfMonsters] = selectMonster(level->level);
      setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[i], level->tiles);
      level->numberOfMonsters++;
    }
  }
}

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
    { WHITE, PINK, RED },
    { WHITE, ORANGE, RED },
    { ORANGE, WHITE, CYAN }
  };

  int monstersStats[3][3][3] = {
    {
    // HP, Atk, Def
      { 2, 1, 1 }, // Spider
      { 3, 2, 2 }, // Giant Spider
      { 3, 3, 2 }  // Scorpion
    },
    {
      { 4, 3, 1 }, // Goblin
      { 5, 4, 2 }, // Hobgoblin
      { 6, 4, 4 }  // Orc
    },
    {
      { 15, 5, 4 }, // Troll
      { 15, 5, 4 }, // Ice Troll
      { 15, 5, 4 }  // Water Troll
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

Monster * createMonster(char name[20], char symbol, int stats[3], int color) {
  Monster * newMonster = malloc(sizeof(Monster));
  
  strcpy(newMonster->name, name);
  newMonster->symbol = symbol;
  newMonster->color = color;
  newMonster->stats.health = stats[0];
  newMonster->stats.attack = stats[1];
  newMonster->stats.defence = stats[2];
  newMonster->seeking = false;

  return newMonster;
}

void setStartingPosition(Monster * monster, Room * room, char ** tiles) {
  monster->position = malloc(sizeof(Position));
  monster->position->x = (rand() % (room->width - 2)) + room->position.x + 1;
  monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;
  drawUnit(tiles, monster->position, 0, 0, monster->symbol, monster->color);
}

void moveMonsters(Monster ** monsters, int numberOfMonsters, Player * player, char ** tiles) {
  for (int i = 0; i < numberOfMonsters; i++) {
    Position offset;
    if (monsters[i]->seeking) {
      offset = seek(monsters[i]->position, player->position);
      drawUnit(tiles, monsters[i]->position, offset.x, offset.y,
        monsters[i]->symbol, monsters[i]->color);
    } else {
      offset = wander(monsters[i]->position);
      drawUnit(tiles, monsters[i]->position, offset.x, offset.y,
        monsters[i]->symbol, monsters[i]->color);
    }
    monsters[i]->position->x += offset.x;
    monsters[i]->position->y += offset.y;
  }
}

Position wander(Position * monterPosition) {
  Position offset;
  offset.x = (rand() % 3) - 1;
  offset.y = (rand() % 3) - 1;
  if (!checkPosition(offset.x, offset.y, monterPosition)) {
    offset.x = 0;
    offset.y = 0;
  }
  return offset;
}

Position seek(Position * monsterPosition, Position * destination) {
  Position offset;
  offset.x = 0;
  offset.y = 0;
  if ((abs((monsterPosition->y - 1) - destination->y) < abs(monsterPosition->y - destination->y))
    && checkPosition(0, -1, monsterPosition)) {
    offset.y -= 1;
  }
  else if ((abs((monsterPosition->x + 1) - destination->x) < abs(monsterPosition->x - destination->x))
    && checkPosition(1, 0, monsterPosition)) {
    offset.x += 1;
  }
  else if ((abs((monsterPosition->y + 1) - destination->y) < abs(monsterPosition->y - destination->y)) 
    && checkPosition(0, 1, monsterPosition)) {
    offset.y += 1;
  }
  else if ((abs((monsterPosition->x - 1) - destination->x) < abs(monsterPosition->x - destination->x))
    && checkPosition(-1, 0, monsterPosition)) {
    offset.x -= 1;
  }
  return offset;
}