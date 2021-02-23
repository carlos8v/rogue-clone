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

/**
 * Executa os inputs devidos e retorna se o jogador deveria se mover
 *
 * @param int input
 * @param Player player
 * @param Level* level
 * @return boolean
 */
bool handleInput(int input) {
  Player * player = dungeon->player;
  Position offset;
  offset.x = 0;
  offset.y = 0;

  bool shouldMove = false;

  switch(input) {
    case '1': case '2': case '3': case '4':
    case '6': case '7': case '8': case '9': case 'w':
    case 'a': case 's': case 'd': case KEY_UP: case KEY_LEFT:
    case KEY_RIGHT: case KEY_DOWN:
      if (input == 'w' || input == '8') offset.y = -1;
      else if (input == 'a' || input == '4') offset.x = -1;
      else if (input == 's' || input == '2') offset.y = 1;
      else if (input == 'd' || input == '6') offset.x = 1;
      else if (input == '1' || input == KEY_LEFT) { offset.x = -1; offset.y = 1; }
      else if (input == '3' || input == KEY_DOWN) { offset.x = 1; offset.y = 1; }
      else if (input == '7' || input == KEY_UP) { offset.x = -1; offset.y = -1; }
      else if (input == '9' || input == KEY_RIGHT) { offset.x = 1; offset.y = -1; }
      if (checkUnits(player->position, offset.x, offset.y) == MONSTER) {
        Position enemyPosition;
        enemyPosition.x = player->position->x + offset.x;
        enemyPosition.y = player->position->y + offset.y;
        attack(player->stats, enemyPosition, MONSTER);
        shouldMove = true;
      }
      else if (checkPosition(player->position, offset.x, offset.y)) {
        char ** unitsMap = dungeon->levels[dungeon->currentLevel]->unitsMap;
        changeUnitsMap(unitsMap, player->position, offset.x, offset.y, player->symbol);
        player->position->x += offset.x;
        player->position->y += offset.y;
        shouldMove = true;
      }
      break;
    case '.':
      printResult("Você descansou...");
      shouldMove = true;
      break;
    case 0:
      break;
    default:
      printResult("Input: Comando não encontrado;");
      break;
  }
  debug(input);
  return shouldMove;
}
