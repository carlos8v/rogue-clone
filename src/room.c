#include "nethack.h"

Room * createRoom(int x, int y, int height, int width) {
  Room * newRoom = malloc(sizeof(Room));
  newRoom->position.x = x;
  newRoom->position.y = y;
  newRoom->height = height;
  newRoom->width = width;

  newRoom->doors[0].x = (rand() % (width - 1)) + x + 1;
  newRoom->doors[0].y = y;

  newRoom->doors[1].x = (rand() % (width - 1)) + x + 1;
  newRoom->doors[1].y = y + height;

  newRoom->doors[2].y = (rand() % (height - 1)) + y + 1;
  newRoom->doors[2].x = x;

  newRoom->doors[3].y = (rand() % (height - 1)) + y + 1;
  newRoom->doors[3].x = x + width - 1;

  return newRoom;
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

  mvprintw(room->doors[0].y, room->doors[0].x, "+");
  mvprintw(room->doors[1].y, room->doors[1].x, "+");
  mvprintw(room->doors[2].y, room->doors[2].x, "+");
  mvprintw(room->doors[3].y, room->doors[3].x, "+");
}