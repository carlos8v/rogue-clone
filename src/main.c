#include "rogue.h"

int main() {
  if (!screenSetup()) return 0;

  dungeon = dungeonSetup();

  drawLevel();

  int input = 0;
  int monsterMove = 0;

  do {
    clearResult();
    if (handleInput(input)) {
      if (++monsterMove > 1) {
        moveMonsters();
        monsterMove = 0;
      }
      if (dungeon->player->stats->health <= 0) break;
      drawLevel();
    }
    refreshScreens();
  } while ((input = getch()) != 'Q');

  endwin();

  return 0;
}
