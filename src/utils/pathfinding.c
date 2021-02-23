#include "nethack.h"

/**
 * Adiciona os tiles vizinhos e retorna o frontierCount atualizado
 * 
 * @param Position* frontier
 * @param int frontierCount
 * @param Position** cameFrom
 * @param bool ** visited
 * @param Position position 
 * @return int frontierCount
 */
int addNeighbors(Position * frontier, int frontierCount, Position ** cameFrom, bool ** visited, Position position, bool ** rules) {
  if (!outOfBounds(position, 0, -1)) {
    if (!visited[position.y - 1][position.x] && rules[position.y - 1][position.x]) {
      frontier[frontierCount].x = position.x;
      frontier[frontierCount].y = position.y - 1;
      cameFrom[position.y - 1][position.x] = position;
      visited[position.y - 1][position.x] = true;
      frontierCount++;
    }
  }

  if (!outOfBounds(position, 1, 0)) {
    if (!visited[position.y][position.x + 1] && rules[position.y][position.x + 1]) {
      frontier[frontierCount].x = position.x + 1;
      frontier[frontierCount].y = position.y;
      cameFrom[position.y][position.x + 1] = position;
      visited[position.y][position.x + 1] = true;
      frontierCount++;
    }
  }

  if (!outOfBounds(position, 0, 1)) {
    if (!visited[position.y + 1][position.x] && rules[position.y + 1][position.x]) {
      frontier[frontierCount].x = position.x;
      frontier[frontierCount].y = position.y + 1;
      cameFrom[position.y + 1][position.x] = position;
      visited[position.y + 1][position.x] = true;
      frontierCount++;
    }
  }

  if (!outOfBounds(position, -1, 0)) {
    if (!visited[position.y][position.x - 1] && rules[position.y][position.x - 1]) {
      frontier[frontierCount].x = position.x - 1;
      frontier[frontierCount].y = position.y;
      cameFrom[position.y][position.x - 1] = position;
      visited[position.y][position.x - 1] = true;
      frontierCount++;
    }
  }

  return frontierCount;
}

/**
 * Retorna uma lista com as coordenadas até certa posição
 * 
 * @param Position initial
 * @param Position final
 * @param bool** rules
 * @return Position** cameFrom
 */
Position ** getPath(Position initial, Position final, bool ** rules) {
  Position * frontier = malloc(sizeof(Position) * (MAP_WIDTH + 1) * (MAP_HEIGHT + 1));
  Position ** cameFrom = malloc(sizeof(Position *) * (MAP_HEIGHT + 1));
  bool ** visited = malloc(sizeof(bool *) * (MAP_HEIGHT + 1));

  for (int j = 0; j <= MAP_HEIGHT; j++) {
    cameFrom[j] = malloc(sizeof(Position) * (MAP_WIDTH + 1));
    visited[j] = malloc(sizeof(bool) * (MAP_WIDTH + 1));
    for (int i = 0; i <= MAP_WIDTH; i++) {
      cameFrom[j][i].x = -1;
      cameFrom[j][i].y = -1;
      visited[j][i] = false;
    }
  }

  int frontierIndex = 0;
  int frontierCount = 0;

  frontier[frontierIndex].x = initial.x;
  frontier[frontierIndex].y = initial.y;
  visited[initial.y][initial.x] = true;
  frontierCount++;

  Position position;
  position.x = 0;
  position.y = 0;

  while(frontierIndex < frontierCount) {
    position.x = frontier[frontierIndex].x;
    position.y = frontier[frontierIndex].y;

    if (position.x == final.x && position.y == final.y) break;
    if (frontierCount > (MAP_WIDTH + 1) * (MAP_HEIGHT + 1)) break;

    frontierCount = addNeighbors(frontier, frontierCount, cameFrom, visited, position, rules);
    frontierIndex++;
  }

  free(frontier);
  free(visited);
  free(rules);

  return cameFrom;
}