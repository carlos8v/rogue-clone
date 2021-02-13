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
    symbol: o
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
      return createMonster('x', 2, 1, 1, false, 5);
      break;
    case 2: // Goblin
      return createMonster('o', 5, 3, 1, true, 5);
      break;
    case 3: // Troll
      return createMonster('T', 15, 5, 1, false, 5);
      break;
  }
}

Monster * createMonster(char symbol, int health, int attack, int defence, int seeking, int color) {
  Monster * newMonster = malloc(sizeof(Monster));
  
  newMonster->color = color;
  newMonster->symbol = symbol;
  newMonster->stats.health = health;
  newMonster->stats.attack = attack;
  newMonster->stats.defence = defence;
  newMonster->seeking = seeking;

  return newMonster;
}

void setStartingPosition(Monster * monster, Room * room, char ** tiles) {
  monster->position = malloc(sizeof(Position));
  monster->position->x = (rand() % (room->width - 2)) + room->position.x + 1;
  monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;
  drawUnit(tiles, monster->position, 0, 0, monster->symbol, monster->color);
}

void moveMonsters(Level * level, Player * player) {
  for (int i = 0; i < level->numberOfMonsters; i++) {
    if (level->monsters[i]->seeking) {
      Position offset = seek(level->monsters[i]->position, player->position);
      drawUnit(level->tiles, level->monsters[i]->position, offset.x, offset.y,
        level->monsters[i]->symbol, level->monsters[i]->color);
      level->monsters[i]->position->x += offset.x;
      level->monsters[i]->position->y += offset.y;
    }
  }
}

Position seek(Position * monsterPosition, Position * destination) {
  Position offset;
  offset.x = 0;
  offset.y = 0;
  if ((abs((monsterPosition->y - 1) - destination->y) < abs(monsterPosition->y - destination->y))
    && ((mvinch(monsterPosition->y - 1, monsterPosition->x) == '.')
    || (mvinch(monsterPosition->y - 1, monsterPosition->x) == '#')
    || (mvinch(monsterPosition->y - 1, monsterPosition->x) == '+'))) {
    offset.y -= 1;
  }
  else if ((abs((monsterPosition->x + 1) - destination->x) < abs(monsterPosition->x - destination->x))
    && ((mvinch(monsterPosition->y, monsterPosition->x + 1) == '.')
    || (mvinch(monsterPosition->y, monsterPosition->x + 1) == '#')
    || (mvinch(monsterPosition->y, monsterPosition->x + 1) == '+'))) {
    offset.x += 1;
  }
  else if ((abs((monsterPosition->y + 1) - destination->y) < abs(monsterPosition->y - destination->y)) 
    && ((mvinch(monsterPosition->y + 1, monsterPosition->x) == '.')
    || (mvinch(monsterPosition->y + 1, monsterPosition->x) == '#')
    || (mvinch(monsterPosition->y + 1, monsterPosition->x) == '+'))){
    offset.y += 1;
  }
  else if ((abs((monsterPosition->x - 1) - destination->x) < abs(monsterPosition->x - destination->x))
    && ((mvinch(monsterPosition->y, monsterPosition->x - 1) == '.')
    || (mvinch(monsterPosition->y, monsterPosition->x - 1) == '#')
    || (mvinch(monsterPosition->y, monsterPosition->x - 1) == '+'))) {
    offset.x -= 1;
  }
  return offset;
}