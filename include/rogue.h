#ifndef ROGUE_H
#define ROGUE_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Stats {
  int health;
  int maxHealth;
  int attack;
  int defence;
  int vision;
} Stats;

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Monster {
  char name[20];
  char symbol;
  int color;
  bool seeking;
  Stats * stats;
  Position * position;
} Monster;

typedef struct Player {
  char name[20];
  char title[20];
  char symbol;
  int color;
  Stats * stats;
  Position * position;
} Player;

typedef struct Item {} Item;

typedef struct Room {
  int height;
  int width;
  Position position;
  Position ** doors;
} Room;

typedef struct Level {
  int level;
  char ** tiles;
  char ** unitsMap;
  
  int numberOfRooms;
  Room ** rooms;

  int numberOfMonsters;
  Monster ** monsters;

  int numberOfItems;
  Item ** items;
} Level;

typedef struct Dungeon {
  int currentLevel;
  int numberOfLevels;
  Player * player;
  Level ** levels;
} Dungeon;

#define WHITE 1
#define CYAN 2
#define GREEN 3
#define YELLOW 4
#define ORANGE 5
#define RED 6
#define PURPLE 7
#define BLUE 8

#define MAP_WIDTH 79
#define MAP_HEIGHT 19

enum TILE { VOID, FLOOR, PLAYER, MONSTER, ITEM };

WINDOW * resscr;
WINDOW * mapscr;
WINDOW * statscr;

Dungeon * dungeon;

bool screenSetup();
void createBorders();
void drawLevel();
void drawStats();
void drawUnit(Position * position, char symbol, int color);

void refreshScreens();
void clearResult();
void printResult(char result[79]);

short * getColorFormat(int red, int green, int blue);
void debug(char input);
void printColors();

bool handleInput(int input);

Dungeon * dungeonSetup();

Level * createLevel(int level);

char ** saveTiles();
char ** initializeUnitsMap();
void changeUnitsMap(char ** unitsMap, Position * position, int xOffset, int yOffset, char symbol);
bool outOfBounds(Position position, int xOffset, int yOffset);
int checkUnits(Position * position, int xOffset, int yOffset);
bool checkPosition(Position position, int xOffset, int yOffset);

Player * playerSetup();

void addMonsters(Level * level);
Monster * selectMonster(int level);
Monster * createMonster(char name[20], char symbol, int stats[4], int color);
void setStartingPosition(Monster * monster, Room * room);

void moveMonsters();
Position seek(Position * monsterPosition, Position * destination);
Position wander(Position * monsterPosition);

int addNeighbors(Position * frontier, int frontierCount, Position ** cameFrom, bool ** visited, Position position, bool ** rules);
Position ** getPath(Position initial, Position final, bool ** rules);

double getDistance(Position initial, Position final, bool oval);
bool isInRange(Position initial, Position final, int range, bool perspective, bool smooth);
void attack(Stats * unit, Position enemyPosition, int enemyType);

Room ** roomsSetup(char ** tiles);
Room * createRoom(int x, int y, int height, int width);
void saveRoom(Room * room, char ** tiles);
void connectDoors(Position * doorOne, Position * doorTwo, char ** tiles);
#endif
