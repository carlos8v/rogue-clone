#include "nethack.h"

void debug(char input, Player * player) {
  mvprintw(36, 0, "Input: %c", input);
  mvprintw(37, 0, "Player: %i, %i", player->position.x, player->position.y);
  move(player->position.y, player->position.x);
}

void createBorders() {
  for (int j = 0; j <= 30; j+=30) {
    for (int i = 0; i <= 100; i++) {
      mvprintw(j, i, "*");
    }
  }

  for (int i = 0; i <= 100; i+=100) {
    for (int j = 1; j < 30; j++) {
      mvprintw(j, i, "*");
    }
  }
}

void screenSetup() {
  initscr();
  srand(time(NULL));
  noecho();

  createBorders();
}

void drawRoom(Room * room) {
  int i, j;
  for (i = room->position.x; i < room->position.x + room->width; i++) {
    mvprintw(room->position.y, i, "-");
    mvprintw(room->position.y + room->height, i, "-");
    for (j = room->position.y + 1; j < room->position.y + room->height; j++) {
      if (i == room->position.x || i == room->position.x + room->width - 1) {
        mvprintw(j, i, "|");
      } else {
        mvprintw(j, i, ".");
      }
    }
  }

  mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
  mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
  mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
  mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
}

void drawUnit(char ** tiles, Position position, int xOffset, int yOffset, char symbol) {
  char buffer[8];
  sprintf(buffer, "%c", tiles[position.y][position.x]);
  mvprintw(position.y, position.x, buffer);
  
  mvprintw(position.y + yOffset, position.x + xOffset, "%c", symbol);
  move(position.y + yOffset, position.x + xOffset);
}
