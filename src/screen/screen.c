#include "rogue.h"

/**
 * Printa na tela informações úteis para debugger
 * 
 * @param char input
 */
void debug(char input) {
  Player * player = dungeon->player;
  mvwprintw(statscr, 0, 40, "Input: %c ", input);
  mvwprintw(statscr, 1, 40, "Player: %i, %i", player->position->x, player->position->y);
}

/**
 * Printa na tela todos os conjutos de cores
 */
void printColors() {
  for (int j = 0; j < 4; j++) {
    if (j == 1) attron(A_BOLD);
    else if (j == 2) attron(A_REVERSE);
    else if (j == 3) attron(A_REVERSE | A_BOLD);
    for (int i = 0; i < 8; i++) {
      attron(COLOR_PAIR(i + 1));
      mvprintw(i, j * 5, "Test");
      attroff(COLOR_PAIR(i + 1));
    }
    attroff(A_BOLD | A_REVERSE);
  }
  getch();
}

/**
 * Inicializa as configurações iniciais da tela
 * @return bool
 */
bool screenSetup() {
  initscr();

  if (has_colors()) start_color();
  if (can_change_color()) {
    short * bg_color = getColorFormat(40, 42, 54);
    short * fg_color = getColorFormat(255, 255, 255);
    short * cyan_color = getColorFormat(139, 233, 253);
    short * green_color = getColorFormat(80, 250, 123);
    short * yellow_color = getColorFormat(242, 208, 12);
    short * orange_color = getColorFormat(255, 164, 45);
    short * red_color = getColorFormat(255, 85, 85);
    short * purple_color = getColorFormat(227, 97, 232);
    short * blue_color = getColorFormat(71, 116, 252);

    init_color(0, bg_color[0], bg_color[1], bg_color[2]);
    init_color(1, cyan_color[0], cyan_color[1], cyan_color[2]);
    init_color(2, green_color[0], green_color[1], green_color[2]);
    init_color(3, yellow_color[0], yellow_color[1], yellow_color[2]);
    init_color(4, orange_color[0], orange_color[1], orange_color[2]);
    init_color(5, red_color[0], red_color[1], red_color[2]);
    init_color(6, purple_color[0], purple_color[1], purple_color[2]);
    init_color(7, fg_color[0], fg_color[1], fg_color[2]);

    init_color(8, bg_color[0], bg_color[1], bg_color[2]);
    init_color(9, cyan_color[0], cyan_color[1], cyan_color[2]);
    init_color(10, green_color[0], green_color[1], green_color[2]);
    init_color(11, yellow_color[0], yellow_color[1], yellow_color[2]);
    init_color(12, orange_color[0], orange_color[1], orange_color[2]);
    init_color(13, red_color[0], red_color[1], red_color[2]);
    init_color(14, purple_color[0], purple_color[1], purple_color[2]);
    init_color(15, fg_color[0], fg_color[1], fg_color[2]);

    init_color(16, blue_color[0], blue_color[1], blue_color[2]);

    init_pair(WHITE, 7, 0);
    init_pair(CYAN, 1, 0);
    init_pair(GREEN, 2, 0);
    init_pair(YELLOW, 3, 0);
    init_pair(ORANGE, 4, 0);
    init_pair(RED, 5, 0);
    init_pair(PURPLE, 6, 0);
    init_pair(BLUE, 16, 0);

    // wattron(stdscr, COLOR_PAIR(1));
  } else {
    mvprintw(0, 0, "Seu terminal não aceita cores");
    getch();
    endwin();
    return false;
  }

  resscr = newwin(1, 80, 0, 0);
  mapscr = newwin(20, 80, 1, 0);
  statscr = newwin(2, 80, 22, 0);
  refresh();

  keypad(stdscr, TRUE);
  srand(time(NULL));
  noecho();

  return true;
}

short * getColorFormat(int red, int green, int blue) {
  short * color = malloc(sizeof(short) * 3);
  color[0] = (red * 1000) / 255;
  color[1] = (green * 1000) / 255;
  color[2] = (blue * 1000) / 255;
  return color;
}

void refreshScreens() {
  wmove(mapscr, dungeon->player->position->y, dungeon->player->position->x);
  wrefresh(statscr);
  wrefresh(resscr);
  wrefresh(mapscr);
}

/**
 * Printa na tela o layout do mapa, os monstros e o jogador
 */
void drawLevel() {
  Level * level = dungeon->levels[dungeon->currentLevel];
  Player * player = dungeon->player;

  for (int j = 0; j <= MAP_HEIGHT; j++) {
    for (int i = 0; i <= MAP_WIDTH; i++) {
      Position position;
      position.x = i;
      position.y = j;

      int displayColor;

      switch(level->tiles[j][i]) {
        case '+': displayColor = YELLOW; break;
        default: displayColor = WHITE; break;
      }

      if (isInRange(*player->position, position, player->stats->vision, false, false)
        && level->tiles[j][i] == '#')
        displayColor = ORANGE;

      wattron(mapscr, COLOR_PAIR(displayColor));
      mvwprintw(mapscr, j, i, "%c", level->tiles[j][i]);
      wattroff(mapscr, COLOR_PAIR(displayColor));
    }
  }

  for (int i = 0; i < level->numberOfMonsters; i++) {
    if (level->monsters[i]->stats->health <= 0)
      drawUnit(level->monsters[i]->position, '%', WHITE);
    else
      drawUnit(level->monsters[i]->position, level->monsters[i]->symbol, level->monsters[i]->color);
  }

  drawUnit(player->position, player->symbol, player->color);
  drawStats();
  wmove(mapscr, player->position->y, player->position->x);
}

/**
 * Printa na tela o caractére do personagem (Jogador ou monstro)
 * 
 * @param Position* position
 * @param char symbol
 * @param int color
 */
void drawUnit(Position * position, char symbol, int color) {
  wattron(mapscr, COLOR_PAIR(color));
  mvwprintw(mapscr, position->y, position->x, "%c", symbol);
  wattroff(mapscr, COLOR_PAIR(color));
}

void clearResult() {
  wmove(resscr, 0, 0);
  for (int i = 0; i < 80; i++) mvwprintw(resscr, 0, i, " ");
}

void printResult(char result[79]) {
  mvwprintw(resscr, 0, 0, "%s", result);
}

void drawStats() {
  Stats * stats = dungeon->player->stats;

  int colorDisplay;
  int titleCounter = 0;
  bool nameIsDone = false;
  bool titleIsDone = false;
  int healthBarIndex = (((stats->health * 100) / stats->maxHealth) * 30) / 100;

  mvwprintw(statscr, 0, 0, "[");
  wattron(statscr, A_REVERSE);
  for (int i = 0; i < 30; i++) {
    if (healthBarIndex == 30) colorDisplay = WHITE;
    else if (healthBarIndex >= 22) colorDisplay = GREEN;
    else if (healthBarIndex >= 15) colorDisplay = YELLOW;
    else if (healthBarIndex > 7) colorDisplay = ORANGE;
    else colorDisplay = RED;
    if (healthBarIndex <= 15) wattron(statscr, A_BOLD);
    wattron(statscr, COLOR_PAIR(colorDisplay));

    if (!nameIsDone) {
      wprintw(statscr, "%c", dungeon->player->name[i]);
      if (dungeon->player->name[i + 1] == '\0') {
        wprintw(statscr, " ");
        nameIsDone = true;
      }
    } else if (!titleIsDone) {
      wprintw(statscr, "%c", dungeon->player->title[titleCounter]);
      if (dungeon->player->title[titleCounter + 1] == '\0') titleIsDone = true;
      titleCounter++;
    } else {
      wprintw(statscr, " ");
    }

    wattroff(statscr, COLOR_PAIR(colorDisplay) | A_BOLD);
    if (i >= (healthBarIndex - 1)) wattroff(statscr, A_REVERSE);
  }
  wprintw(statscr, "]");

  mvwprintw(statscr, 1, 0, "Floor:%i ", dungeon->currentLevel + 1);
  wprintw(statscr, "HP:%i(%i) ", stats->health, stats->maxHealth);
  wprintw(statscr, "Atk:%i ", stats->attack);
  wprintw(statscr, "Def:%i ", stats->defence);
}
