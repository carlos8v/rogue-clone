#include "nethack.h"

int main() {
  if (!screenSetup()) return 0;

  Level * level = createLevel(1);

  int input = 0;
  Player * player = playerSetup(level->tiles);

  int monsterMove = 0;
  do {
    if (handleInput(input, player, level->tiles)) {
      if (++monsterMove > 1) {
        moveMonsters(level->monsters, level->numberOfMonsters, player, level->tiles);
        monsterMove = 0;
      }
      move(player->position->y, player->position->x);
    }
  } while ((input = getch()) != 'Q');

  endwin();

  return 0;
}
