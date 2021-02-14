#include "nethack.h"

/**
 * Printa na tela informações úteis para debugger
 * 
 * @param char input
 */
void debug(char input) {
  Player * player = dungeon->player;
  mvprintw(21, 0, "Input: %c ", input);
  mvprintw(22, 0, "Player: %i, %i", player->position->x, player->position->y);
  move(player->position->y, player->position->x);
}

/**
 * Printa na tela todos os conjutos de cores
 */
void printColors() {
  attron(COLOR_PAIR(1));
  mvprintw(0, 0, "Teste");
  attron(COLOR_PAIR(2));
  mvprintw(1, 0, "Teste");
  attron(COLOR_PAIR(3));
  mvprintw(2, 0, "Teste");
  attron(COLOR_PAIR(4));
  mvprintw(3, 0, "Teste");
  attron(COLOR_PAIR(5));
  mvprintw(4, 0, "Teste");
  attron(COLOR_PAIR(6));
  mvprintw(5, 0, "Teste");
  attron(COLOR_PAIR(7));
  mvprintw(6, 0, "Teste");

  attron(COLOR_PAIR(1) | A_REVERSE);
  mvprintw(0, 6, "Teste");
  attron(COLOR_PAIR(2) | A_REVERSE);
  mvprintw(1, 6, "Teste");
  attron(COLOR_PAIR(3) | A_REVERSE);
  mvprintw(2, 6, "Teste");
  attron(COLOR_PAIR(4) | A_REVERSE);
  mvprintw(3, 6, "Teste");
  attron(COLOR_PAIR(5) | A_REVERSE);
  mvprintw(4, 6, "Teste");
  attron(COLOR_PAIR(6) | A_REVERSE);
  mvprintw(5, 6, "Teste");
  attron(COLOR_PAIR(7) | A_REVERSE);
  mvprintw(6, 6, "Teste");
  attroff(COLOR_PAIR(7) | A_REVERSE);

  refresh();
  wrefresh(stdscr);
  getch();
}

/**
 * Inicializa as configurações iniciais da tela
 * @returns bool
 */
bool screenSetup() {
  initscr();
  start_color();

  if (can_change_color()) {
    short bg_color[3] = { 156.862745098, 164.705882353, 211.764705882 };
    short fg_color[3] = { 1000, 1000, 1000 };
    short green_color[3] = { 313.725490196, 1000, 482.352941176 };
    short cyan_color[3] = { 545.098039216, 913.725490196, 992.156862745 };
    short orange_color[3] = { 1000, 721.568627451, 423.529411765 };
    short red_color[3] = { 1000, 333.333333333, 333.333333333 };
    short yellow_color[3] = { 945.098039216, 1000, 549.019607843 };
    short pink_color[3] = { 1000, 474.509803922, 776.470588235 };

    init_color(0, bg_color[0], bg_color[1], bg_color[2]);
    init_color(1, green_color[0], green_color[1], green_color[2]);
    init_color(2, cyan_color[0], cyan_color[1], cyan_color[2]);
    init_color(3, orange_color[0], orange_color[1], orange_color[2]);
    init_color(4, red_color[0], red_color[1], red_color[2]);
    init_color(5, yellow_color[0], yellow_color[1], yellow_color[2]);
    init_color(6, pink_color[0], pink_color[1], pink_color[2]);
    init_color(7, fg_color[0], fg_color[1], fg_color[2]);

    init_pair(WHITE, 7, 0);
    init_pair(GREEN, 1, 0);
    init_pair(CYAN, 2, 0);
    init_pair(ORANGE, 3, 0);
    init_pair(RED, 4, 0);
    init_pair(YELLOW, 5, 0);
    init_pair(PINK, 6, 0);
    wattron(stdscr, COLOR_PAIR(1));
  } else {
    mvprintw(0, 0, "Seu terminal não aceita cores");
    getch();
    endwin();
    return false;
  }

  keypad(stdscr, TRUE);
  srand(time(NULL));
  noecho();

  return true;
}

/**
 * Printa na tela os caractéries corretos da sala
 * @param Room* room
 */
void drawRoom(Room * room) {
  int i, j;
  for (i = room->position.x; i < room->position.x + room->width; i++) {
    mvprintw(room->position.y, i, "-");
    mvprintw(room->position.y + room->height, i, "-");
    for (j = room->position.y + 1; j < room->position.y + room->height; j++) {
      if (i == room->position.x || i == room->position.x + room->width - 1) {
        mvprintw(j, i, "|");
      } else {
        mvprintw(j, i, ".");
      }
    }
  }

  mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
  mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
  mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
  mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
}

/**
 * Printa na tela o layout do mapa, os monstros e o jogador
 */
void drawLevel() {
  Level * level = dungeon->levels[dungeon->currentLevel];
  Player * player = dungeon->player;

  for (int j = 0; j <= SCREEN_HEIGHT; j++) {
    for (int i = 0; i <= SCREEN_WIDTH; i++) {
      // Sistema de tocha

      // Position position;
      // position.x = i;
      // position.y = j;

      // if (isInRange(*player->position, position, player->stats->vision)) {
      //   attron(COLOR_PAIR(ORANGE));
      //   mvprintw(j, i, "%c", level->tiles[j][i]);
      //   attroff(COLOR_PAIR(ORANGE));
      // } else {
      //   mvprintw(j, i, "%c", level->tiles[j][i]);
      // }
      mvprintw(j, i, "%c", level->tiles[j][i]);
    }
  }

  for (int i = 0; i < level->numberOfMonsters; i++) {
    // Sistema de tocha
    // if (isInRange(*player->position, *level->monsters[i]->position, player->stats->vision)) {
    //   if (level->monsters[i]->stats->health <= 0)
    //     drawUnit(level->monsters[i]->position, '%', WHITE);
    //   else
    //     drawUnit(level->monsters[i]->position, level->monsters[i]->symbol, level->monsters[i]->color);
    // }

    if (level->monsters[i]->stats->health <= 0)
      drawUnit(level->monsters[i]->position, '%', WHITE);
    else
      drawUnit(level->monsters[i]->position, level->monsters[i]->symbol, level->monsters[i]->color);
  }

  drawUnit(player->position, player->symbol, player->color);
}

/**
 * Printa na tela o caractére do personagem (Jogador ou monstro)
 * 
 * @param Position* position
 * @param char symbol
 * @param int color
 */
void drawUnit(Position * position, char symbol, int color) {
  attron(COLOR_PAIR(color));
  mvprintw(position->y, position->x, "%c", symbol);
  attroff(COLOR_PAIR(color));
}
