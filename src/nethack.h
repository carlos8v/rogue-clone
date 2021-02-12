#ifndef NETHACK_H
#define NETHACK_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Level {
  int level;
  char ** tiles;
  
  int numberOfRooms;
  struct Room ** rooms;

  int numberOfMonsters;
  struct Monster ** monsters;

  int numberOfItems;
  struct Item ** items;
} Level;

typedef struct Stats {
  int health;
  int attack;
  int defence;
} Stats;

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Monster {
  char symbol;
  bool seeking;
  Stats stats;
  Position * position;
} Monster;

typedef struct Item {} Item;

typedef struct Room {
  int height;
  int width;
  Position position;
  Position ** doors;
} Room;

typedef struct Player {
  Position * position;
  char symbol;
  Stats stats;
} Player;

void screenSetup();
void createBorders();
void drawRoom(Room * room);
void drawUnit(char ** tiles, Position * position, int xOffset, int yOffset, char symbol);
void debug(char input, Player * player);

bool handleInput(int input, Player * player, char ** tiles);

Level * createLevel(int level);

char ** saveLevelPositions();
bool checkPosition(int xOffset, int yOffset, Position * position);

Player * playerSetup(char ** tiles);

void addMonsters(Level * level);
Monster * selectMonster(int level);
Monster * createMonster(char symbol, int health, int attack, int defence, int pathfinding);
void setStartingPosition(Monster * monster, Room * room, char ** tiles);
void moveMonsters(Level * level, Player * player);
Position seek(Position * monsterPosition, Position * destination);

Room ** roomsSetup();
Room * createRoom(int x, int y, int height, int width);
void connectDoors(Position * doorOne, Position * doorTwo);
#endif
