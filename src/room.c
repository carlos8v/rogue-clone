#include "nethack.h"

/**
 * Cria a estrutura inicial de todas as salas do level atual
 *
 * @returns Room**
 */
Room ** roomsSetup() {
  Room ** rooms = malloc(sizeof(Room) * 3);
  rooms[0] = createRoom(13, 13, 6, 8);
  drawRoom(rooms[0]);

  rooms[1] = createRoom(40, 2, 6, 8);
  drawRoom(rooms[1]);

  rooms[2] = createRoom(40, 10, 6, 12);
  drawRoom(rooms[2]);

  connectDoors(rooms[0]->doors[1], rooms[2]->doors[3]);
  connectDoors(rooms[0]->doors[0], rooms[1]->doors[3]);

  return rooms;
}

/**
 * Retorna uma nova instância da struct Room
 *
 * @returns Room*
 */
Room * createRoom(int x, int y, int height, int width) {
  Room * newRoom = malloc(sizeof(Room));
  newRoom->position.x = x;
  newRoom->position.y = y;
  newRoom->height = height;
  newRoom->width = width;

  newRoom->doors = malloc(sizeof(Position) * 4);

  newRoom->doors[0] = malloc(sizeof(Position));
  newRoom->doors[0]->x = (rand() % (width - 2)) + x + 1;
  newRoom->doors[0]->y = y;

  newRoom->doors[1] = malloc(sizeof(Position));
  newRoom->doors[1]->y = (rand() % (height - 2)) + y + 1;
  newRoom->doors[1]->x = x + width - 1;

  newRoom->doors[2] = malloc(sizeof(Position));
  newRoom->doors[2]->x = (rand() % (width - 2)) + x + 1;
  newRoom->doors[2]->y = y + height;

  newRoom->doors[3] = malloc(sizeof(Position));
  newRoom->doors[3]->y = (rand() % (height - 2)) + y + 1;
  newRoom->doors[3]->x = x;

  return newRoom;
}

/**
 * Cria corredores entre as duas portas passadas
 *
 * @param Position* doorOne
 * @param Position* doorTwo
 */
void connectDoors(Position * doorOne, Position * doorTwo) {
  Position actual, previous;
  
  actual.x = doorOne->x;
  actual.y = doorOne->y;
  previous = actual;

  int count = 0;

  while(1) {
    if ((abs((actual.y - 1) - doorTwo->y) < abs(actual.y - doorTwo->y))
      && (mvwinch(mapscr, actual.y - 1, actual.x) == ' ')) {
      previous.y = actual.y;
      actual.y -= 1;
    }
    else if ((abs((actual.x + 1) - doorTwo->x) < abs(actual.x - doorTwo->x))
      && (mvwinch(mapscr, actual.y, actual.x + 1) == ' ')) {
      previous.x = actual.x;
      actual.x += 1;
    }
    else if ((abs((actual.y + 1) - doorTwo->y) < abs(actual.y - doorTwo->y)) 
      && (mvwinch(mapscr, actual.y + 1, actual.x) == ' ')) {
      previous.y = actual.y;
      actual.y += 1;
    }
    else if ((abs((actual.x - 1) - doorTwo->x) < abs(actual.x - doorTwo->x))
      && (mvwinch(mapscr, actual.y, actual.x - 1) == ' ')) {
      previous.x = actual.x;
      actual.x -= 1;
    } else {
      if (count == 0) {
        actual = previous;
        count++;
        continue;
      } else {
        return;
      }
    }

    mvwprintw(mapscr, actual.y, actual.x, "#");
    wrefresh(mapscr);
  }
}
