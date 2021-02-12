#include "nethack.h"

int main() {
  screenSetup();

  Level * level = createLevel(1);

  int input;
  Player * player = playerSetup(level->tiles);

  while ((input = getch()) != 'Q') {
    handleInput(input, player, level->tiles);
  }

  endwin();

  return 0;
}
