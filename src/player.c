#include "nethack.h"

Player * playerSetup() {
  Player * newPlayer = malloc(sizeof(Player));
  newPlayer->position.x = 15;
  newPlayer->position.y = 15;
  newPlayer->health = 10;
  
  renderPlayer(0, 0, newPlayer);
  
  return newPlayer;
}

void renderPlayer(int xOffset, int yOffset, Player * player) {
  mvprintw(player->position.y, player->position.x, ".");
  mvprintw(player->position.y + yOffset, player->position.x + xOffset, "@");  
  move(player->position.y + yOffset, player->position.x + xOffset);
  player->position.x += xOffset;
  player->position.y += yOffset;
}