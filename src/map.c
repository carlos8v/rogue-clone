#include "nethack.h"

void checkPosition(int xOffset, int yOffset, Player * unit) {

  switch (mvinch(unit->position.y + yOffset, unit->position.x + xOffset)) {
    case '.':
      renderPlayer(xOffset, yOffset, unit);
      break;
    default:
      move(unit->position.y, unit->position.x);
      break;
  }
}

void mapSetup() {
  // Room ** rooms = malloc(sizeof(Room) * 3);
  drawRoom(createRoom(13, 13, 6, 8));
  drawRoom(createRoom(40, 2, 6, 8));
  drawRoom(createRoom(40, 10, 6, 12));
}