#include "nethack.h"

/*
Commands:
  7 8 9
   \|/
  4-.-6         - Standard Moviment
   /|\
  1 2 3

  w, a, s, d    - 4-Direction Moviment
  Arrows        - 4-Direction Diagonal Moviment
  .             - Do nothing;

*/

bool handleInput(int input, Player * player, char ** tiles) {
  int xOffset = 0;
  int yOffset = 0;
  bool shouldMove = false;
  switch(input) {
    case '1': case '2': case '3': case '4':
    case '6': case '7': case '8': case '9': case 'w':
    case 'a': case 's': case 'd': case KEY_UP: case KEY_LEFT:
    case KEY_RIGHT: case KEY_DOWN:
      if (input == 'w' || input == '8') yOffset = -1;
      else if (input == 'a' || input == '4') xOffset = -1;
      else if (input == 's' || input == '2') yOffset = 1;
      else if (input == 'd' || input == '6') xOffset = 1;
      else if (input == '1' || input == KEY_LEFT) { xOffset = -1; yOffset = 1; }
      else if (input == '3' || input == KEY_DOWN) { xOffset = 1; yOffset = 1; }
      else if (input == '7' || input == KEY_UP) { xOffset = -1; yOffset = -1; }
      else if (input == '9' || input == KEY_RIGHT) { xOffset = 1; yOffset = -1; }
      if (checkPosition(xOffset, yOffset, player->position)) {
        drawUnit(tiles, player->position, xOffset, yOffset, player->symbol, player->color);
        player->position->x += xOffset;
        player->position->y += yOffset;
        shouldMove = true;
      }
      break;
    case '.':
      shouldMove = true;
      break;
    case 0:
      break;
    default:
      mvprintw(23, 0, "Input: Comando não encontrado");
      getch();
      mvprintw(23, 0, "                              ");
      break;
  }
  debug(input, player);
  return shouldMove;
}