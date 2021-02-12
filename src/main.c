#include "nethack.h"

int main() {
  screenSetup();

  Level * level = createLevel(1);

  int input;
  Player * player = playerSetup(level->tiles);

  int monsterMove = 0;
  while ((input = getch()) != 'Q') {
    if (handleInput(input, player, level->tiles)) {
      if (++monsterMove > 1) {
        moveMonsters(level, player);
        monsterMove = 0;
      }
      move(player->position->y, player->position->x);
    };
  }

  endwin();

  return 0;
}
