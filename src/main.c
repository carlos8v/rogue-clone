#include "nethack.h"

int main() {
  if (!screenSetup()) return 0;

  dungeon = dungeonSetup();

  drawLevel();
  move(dungeon->player->position->y, dungeon->player->position->x);

  int input = 0;
  int monsterMove = 0;

  do {
    if (handleInput(input)) {
      if (++monsterMove > 1) {
        moveMonsters();
        monsterMove = 0;
      }
      drawLevel();
      move(dungeon->player->position->y, dungeon->player->position->x); 
    }
  } while ((input = getch()) != 'Q');

  endwin();

  return 0;
}
