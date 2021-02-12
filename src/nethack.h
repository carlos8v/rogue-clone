#ifndef NETHACK_H
#define NETHACK_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

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
  Position doors[4];

  Monster ** monsters;
  Item ** items;
} Room;

typedef struct Player {
  Position position;
  int health;
} Player;

void screenSetup();
void mapSetup();
Player * playerSetup();

Room * createRoom(int x, int y, int height, int width);
void drawRoom(Room * room);

void renderPlayer(int xOffset, int yOffset, Player * player);
void handleInput(int input, Player * player);
void checkPosition(int xOffset, int yOffset, Player * unit);
#endif
