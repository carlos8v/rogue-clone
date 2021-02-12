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

typedef struct Monster {} Monster;
typedef struct Item {} Item;

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Room {
  int height;
  int width;
  Position position;
  Position ** doors;
} Room;

typedef struct Player {
  Position position;
  int health;
} Player;

void screenSetup();
void createBorders();
void drawRoom(Room * room);
void drawUnit(char ** tiles, Position position, int xOffset, int yOffset, char ch);
void debug(char input, Player * player);

void handleInput(int input, Player * player, char ** tiles);

Level * createLevel(int level);

char ** saveLevelPositions();
bool checkPosition(int xOffset, int yOffset, Position position);

Player * playerSetup(char ** tiles);

Room ** roomsSetup();
Room * createRoom(int x, int y, int height, int width);
void connectDoors(Position * doorOne, Position * doorTwo);
#endif
