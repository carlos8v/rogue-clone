#include "nethack.h"

/*
Monsters:
  1. Spider:
    symbol: x
    levels: 1-3
    stats:
      health: 2
      attack: 1
      speed: 1
      defence: 1
    pathfinding: 1 (random)
  
  2. Goblin:
    symbol: G
    levels: 1-5,
    stats
      health: 5
      attack: 3
      speed: 1
      defence: 1
    pathfinding: 2 (seeking)

  3. Troll
    symbol: T
    levels: 4-6
    stats:
      health: 15
      attack: 5
      speed: 1
      defence: 1
    pathfinding: 1 (random)
*/

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
  int monsterType;
  switch (level) {
  case 1:
  case 2:
  case 3:
    monsterType = (rand() % 2) + 1;
    break;
  case 4:
  case 5:
    monsterType = (rand() % 2) + 2;
    break;
  case 6:
    monsterType = 3;
    break;
  }

  switch(monsterType) {
    case 1: // Spider
      return createMonster('x', 2, 1, 1, 1);
      break;
    case 2: // Goblin
      return createMonster('G', 5, 3, 1, 2);
      break;
    case 3: // Troll
      return createMonster('T', 15, 5, 1, 1);
      break;
  }
}

Monster * createMonster(char symbol, int health, int attack, int defence, int pathfinding) {
  Monster * newMonster = malloc(sizeof(Monster));
  
  newMonster->symbol = symbol;
  newMonster->stats.health = health;
  newMonster->stats.attack = attack;
  newMonster->stats.defence = defence;
  newMonster->pathfinding = pathfinding;

  return newMonster;
}

void setStartingPosition(Monster * monster, Room * room, char ** tiles) {
  monster->position.x = (rand() % (room->width - 2)) + room->position.x + 1;
  monster->position.y = (rand() % (room->height - 2)) + room->position.y + 1;
  
  drawUnit(tiles, monster->position, 0, 0, monster->symbol);
}
