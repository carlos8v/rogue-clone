#include "rogue.h"

/**
 * Cria a estrutura inicial de todas as salas do level atual
 *
 * @param char** tiles
 * @return Room**
 */
Room ** roomsSetup(char ** tiles) {
  Room ** rooms = malloc(sizeof(Room) * 3);
  rooms[0] = createRoom(13, 13, 6, 8);
  saveRoom(rooms[0], tiles);

  rooms[1] = createRoom(40, 2, 6, 8);
  saveRoom(rooms[1], tiles);

  rooms[2] = createRoom(40, 10, 6, 12);
  saveRoom(rooms[2], tiles);

  connectDoors(rooms[0]->doors[1], rooms[2]->doors[3], tiles);
  connectDoors(rooms[0]->doors[0], rooms[1]->doors[3], tiles);

  return rooms;
}

/**
 * Retorna uma nova instância da struct Room
 *
 * @return Room*
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
void connectDoors(Position * doorOne, Position * doorTwo, char ** tiles) {
  bool ** rules = malloc(sizeof(bool*) * (MAP_HEIGHT + 1));
  for (int j = 0; j <= MAP_HEIGHT; j++) {
    rules[j] = malloc(sizeof(bool) * (MAP_WIDTH + 1));
    for (int i = 0; i <= MAP_WIDTH; i++) {
      if (tiles[j][i] == ' ' || tiles[j][i] == '+') rules[j][i] = true;
      else rules[j][i] = false;
    }
  }
  
  Position ** cameFrom = getPath(*doorOne, *doorTwo, rules);

  Position currentPosition;
  currentPosition.x = cameFrom[doorTwo->y][doorTwo->x].x;
  currentPosition.y = cameFrom[doorTwo->y][doorTwo->x].y;

  while(currentPosition.x != doorOne->x || currentPosition.y != doorOne->y) {
    if (currentPosition.x == -1 || currentPosition.y == -1) break;
    tiles[currentPosition.y][currentPosition.x] = '#';
    currentPosition = cameFrom[currentPosition.y][currentPosition.x];
  }
}

/**
 * Salva no tiles os caracteres corretos da sala
 * 
 * @param Room* room
 * @param char** tiles
 */
void saveRoom(Room * room, char ** tiles) {
  int i, j;
  for (i = room->position.x; i < room->position.x + room->width; i++) {
    tiles[room->position.y][i] = '-';
    tiles[room->position.y + room->height][i] = '-';
    for (j = room->position.y + 1; j < room->position.y + room->height; j++) {
      if (i == room->position.x || i == room->position.x + room->width - 1) {
        tiles[j][i] = '|';
      } else {
        tiles[j][i] = '.';
      }
    }
  }

  tiles[room->doors[0]->y][room->doors[0]->x] = '+';
  tiles[room->doors[1]->y][room->doors[1]->x] = '+';
  tiles[room->doors[2]->y][room->doors[2]->x] = '+';
  tiles[room->doors[3]->y][room->doors[3]->x] = '+';
}