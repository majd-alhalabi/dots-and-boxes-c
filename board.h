#ifndef BOARD_H
#define BOARD_H

#define ROWS 4
#define COLS 5

void init_board();
void print_board();

int draw_line(int r1,int c1,int r2,int c2,char player);
int is_valid_move(int r1,int c1,int r2,int c2);
int is_game_over();
int get_score(char player);

int get_h_line(int i, int j);
int get_v_line(int i, int j);

#endif
