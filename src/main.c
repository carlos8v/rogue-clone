#include "nethack.h"

int main() {
  screenSetup();

  int ch;
  Player * player = playerSetup();

  while ((ch = getch()) != 'q') {
    handleInput(ch, player);
  }

  endwin();

  return 0;
}

void handleInput(int input, Player * player) {
  switch(input) {
    case 'w':
      checkPosition(0, -1, player);
      break;
    case 'a':
      checkPosition(-1, 0, player);
      break;
    case 'd':
      checkPosition(1, 0, player);
      break;
    case 's':
      checkPosition(0, 1, player);
      break;
    default:
      break;
  }
}

void screenSetup() {
  initscr();
  srand(time(NULL));
  noecho();
  mapSetup();  
}
