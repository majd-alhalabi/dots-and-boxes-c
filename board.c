#include <stdio.h>
#include <stdlib.h>
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
                if(j < COLS) printf(" %c ", boxes[i][j]);
            }
            printf("\n");
        }
    }
}

int check_box(int r, int c, char player) {
    if(boxes[r][c] != ' ') return 0;

    if(h_lines[r][c] && h_lines[r+1][c] &&
       v_lines[r][c] && v_lines[r][c+1]) {
        boxes[r][c] = player;
        return 1;
    }
    return 0;
}

int draw_line(int r1, int c1, int r2, int c2, char player) {
    int scored = 0;

    if(r1 == r2 && abs(c1 - c2) == 1) {
        int c = (c1 < c2) ? c1 : c2;
        if(h_lines[r1][c]) return -1;
        h_lines[r1][c] = 1;

        if(r1 > 0) scored += check_box(r1-1, c, player);
        if(r1 < ROWS) scored += check_box(r1, c, player);
    }
    else if(c1 == c2 && abs(r1 - r2) == 1) {
        int r = (r1 < r2) ? r1 : r2;
        if(v_lines[r][c1]) return -1;
        v_lines[r][c1] = 1;

        if(c1 > 0) scored += check_box(r, c1-1, player);
        if(c1 < COLS) scored += check_box(r, c1, player);
    }
    else return -1;

    return scored;
}

int is_game_over() {
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            if(boxes[i][j]==' ') return 0;
    return 1;
}

int get_score(char player) {
    int score=0;
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            if(boxes[i][j]==player) score++;
    return score;
}