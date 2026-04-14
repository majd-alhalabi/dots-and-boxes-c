#include <stdio.h>
#include "board.h"

static int h_lines[ROWS+1][COLS];
static int v_lines[ROWS][COLS+1];
static char boxes[ROWS][COLS];

void init_board() {
    for(int i=0;i<ROWS+1;i++)
        for(int j=0;j<COLS;j++)
            h_lines[i][j]=0;

    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS+1;j++)
            v_lines[i][j]=0;

    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            boxes[i][j]=' ';
}

void print_board() {
    printf("   ");
    for(int j = 0; j < COLS + 1; j++) {
        printf("%d   ", j);
    }
    printf("\n");

    for(int i = 0; i < ROWS + 1; i++) {
        printf("%d  ", i);
        for(int j = 0; j < COLS; j++) {
            printf(".");
            if(h_lines[i][j]) printf("---");
            else printf("   ");
        }
        printf(".\n");

        if(i < ROWS) {
            printf("   ");
            for(int j = 0; j < COLS + 1; j++) {
                if(v_lines[i][j]) printf("|");
                else printf(" ");
                if(j < COLS) {
                    printf(" %c ", boxes[i][j]);
                }
            }
            printf("\n");
        }
    }
}

int is_valid_move(int r1,int c1,int r2,int c2) {

    if(r1 < 0 || r1 > ROWS || c1 < 0 || c1 > COLS) return 0;
    if(r2 < 0 || r2 > ROWS || c2 < 0 || c2 > COLS) return 0;

    if(r1 == r2 && (c1 == c2+1 || c1 == c2-1)) {
        int c = (c1 < c2) ? c1 : c2;
        if(h_lines[r1][c] == 0) return 1;
    }

    if(c1 == c2 && (r1 == r2+1 || r1 == r2-1)) {
        int r = (r1 < r2) ? r1 : r2;
        if(v_lines[r][c1] == 0) return 1;
    }

    return 0;
}

int check_box(int r,int c,char player) {
    if(h_lines[r][c] && h_lines[r+1][c] &&
       v_lines[r][c] && v_lines[r][c+1] &&
       boxes[r][c] == ' ') {
        boxes[r][c] = player;
        return 1;
    }
    return 0;
}

int draw_line(int r1,int c1,int r2,int c2,char player) {

    if(!is_valid_move(r1,c1,r2,c2)) return -1;

    int scored = 0;

    if(r1 == r2) {
        int c = (c1 < c2) ? c1 : c2;
        h_lines[r1][c] = 1;

        if(r1 < ROWS) scored += check_box(r1,c,player);
        if(r1 > 0) scored += check_box(r1-1,c,player);
    }

    if(c1 == c2) {
        int r = (r1 < r2) ? r1 : r2;
        v_lines[r][c1] = 1;

        if(c1 < COLS) scored += check_box(r,c1,player);
        if(c1 > 0) scored += check_box(r,c1-1,player);
    }

    return scored;
}

int is_game_over() {
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            if(boxes[i][j] == ' ') return 0;
    return 1;
}

int get_score(char player) {
    int score = 0;
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            if(boxes[i][j] == player) score++;
    return score;
}

int get_h_line(int i, int j) {
    return h_lines[i][j];
}

int get_v_line(int i, int j) {
    return v_lines[i][j];
}
