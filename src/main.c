#include "nethack.h"

int main() {
  if (!screenSetup()) return 0;

  Dungeon * dungeon = dungeonSetup();

  drawLevel(dungeon->levels[0], dungeon->player);
  move(dungeon->player->position->y, dungeon->player->position->x);

  int input = 0;
  int monsterMove = 0;

  do {
    if (handleInput(input, dungeon->player, dungeon->levels[dungeon->currentLevel])) {
      if (++monsterMove > 1) {
        moveMonsters(
          dungeon->levels[dungeon->currentLevel],
          dungeon->levels[dungeon->currentLevel]->monsters,
          dungeon->levels[dungeon->currentLevel]->numberOfMonsters,
          dungeon->player
        );
        monsterMove = 0;
      }
      drawLevel(dungeon->levels[dungeon->currentLevel], dungeon->player);
      move(dungeon->player->position->y, dungeon->player->position->x); 
    }
  } while ((input = getch()) != 'Q');

  endwin();

  return 0;
}
