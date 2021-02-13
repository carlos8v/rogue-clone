#include "nethack.h"

void debug(char input, Player * player) {
  mvprintw(36, 0, "Input: %c                      ", input);
  mvprintw(37, 0, "Player: %i, %i", player->position->x, player->position->y);
  move(player->position->y, player->position->x);
}

void createBorders() {
  for (int j = 0; j <= 30; j+=30) {
    for (int i = 0; i <= 100; i++) {
      mvprintw(j, i, "*");
    }
  }

  for (int i = 0; i <= 100; i+=100) {
    for (int j = 1; j < 30; j++) {
      mvprintw(j, i, "*");
    }
  }
}

void screenSetup() {
  initscr();
  start_color();
  // #define COLOR_BLACK	0
  // #define COLOR_RED	1
  // #define COLOR_GREEN	2
  // #define COLOR_YELLOW	3
  // #define COLOR_BLUE	4
  // #define COLOR_MAGENTA	5
  // #define COLOR_CYAN	6
  // #define COLOR_WHITE	7

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
    
    init_pair(1, 7, 0); // Branco
    init_pair(2, 1, 0); // Verde
    init_pair(3, 2, 0); // Ciano
    init_pair(4, 3, 0); // Laranja
    init_pair(5, 4, 0); // Vermelho
    init_pair(6, 5, 0); // Amarelo
    init_pair(7, 6, 0); // Rosa
  }

  keypad(stdscr, TRUE);
  srand(time(NULL));
  noecho();

  createBorders();
}

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

void drawUnit(char ** tiles, Position * position, int xOffset, int yOffset, char symbol, int color) {
  mvprintw(position->y, position->x, "%c", tiles[position->y][position->x]);
  attron(COLOR_PAIR(color));
  mvprintw(position->y + yOffset, position->x + xOffset, "%c", symbol);
  attroff(COLOR_PAIR(color));
}
