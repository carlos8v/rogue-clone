#ifndef NETHACK_H
#define NETHACK_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
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
  char name[20];
  char symbol;
  bool seeking;
  Stats stats;
  int color;
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
  int color;
  Stats stats;
} Player;

#define WHITE 1
#define GREEN 2
#define CYAN 3
#define ORANGE 4
#define RED 5
#define YELLOW 6
#define PINK 7

int screenSetup();
void createBorders();
void drawRoom(Room * room);
void drawUnit(char ** tiles, Position * position, int xOffset, int yOffset, char symbol, int color);

void debug(char input, Player * player);
void printColors();

bool handleInput(int input, Player * player, char ** tiles);

Level * createLevel(int level);

char ** saveLevelPositions();
bool checkPosition(int xOffset, int yOffset, Position * position);

Player * playerSetup(char ** tiles);

void addMonsters(Level * level);
Monster * selectMonster(int level);
Monster * createMonster(char name[20], char symbol, int stats[3], int color);
void setStartingPosition(Monster * monster, Room * room, char ** tiles);
void moveMonsters(Monster ** monsters, int numberOfMonsters, Player * player, char ** tiles);
Position seek(Position * monsterPosition, Position * destination);
Position wander(Position * monsterPosition);

Room ** roomsSetup();
Room * createRoom(int x, int y, int height, int width);
void connectDoors(Position * doorOne, Position * doorTwo);
#endif
