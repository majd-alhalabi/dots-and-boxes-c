#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "bot.h"

int count_edges(int i, int j) {
    int count = 0;
    if(get_h_line(i,j)) count++;
    if(get_h_line(i+1,j)) count++;
    if(get_v_line(i,j)) count++;
    if(get_v_line(i,j+1)) count++;
    return count;
}

int try_complete_box(int *r1,int *c1,int *r2,int *c2) {
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {

            if(count_edges(i,j) == 3) {

                if(!get_h_line(i,j)) {
                    if(is_valid_move(i,j,i,j+1)) {
                        *r1=i; *c1=j; *r2=i; *c2=j+1;
                        return 1;
                    }
                }

                if(!get_h_line(i+1,j)) {
                    if(is_valid_move(i+1,j,i+1,j+1)) {
                        *r1=i+1; *c1=j; *r2=i+1; *c2=j+1;
                        return 1;
                    }
                }

                if(!get_v_line(i,j)) {
                    if(is_valid_move(i,j,i+1,j)) {
                        *r1=i; *c1=j; *r2=i+1; *c2=j;
                        return 1;
                    }
                }

                if(!get_v_line(i,j+1)) {
                    if(is_valid_move(i,j+1,i+1,j+1)) {
                        *r1=i; *c1=j+1; *r2=i+1; *c2=j+1;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int creates_third_edge(int r1,int c1,int r2,int c2) {

    if(r1 == r2) {
        int c = (c1 < c2) ? c1 : c2;

        if(r1 > 0 && count_edges(r1-1, c) == 2) return 1;
        if(r1 < ROWS && count_edges(r1, c) == 2) return 1;
    }

    if(c1 == c2) {
        int r = (r1 < r2) ? r1 : r2;

        if(c1 > 0 && count_edges(r, c1-1) == 2) return 1;
        if(c1 < COLS && count_edges(r, c1) == 2) return 1;
    }

    return 0;
}

int try_safe_move(int *r1,int *c1,int *r2,int *c2) {

    for(int i=0;i<ROWS+1;i++) {
        for(int j=0;j<COLS;j++) {

            if(!get_h_line(i,j)) {
                if(!creates_third_edge(i,j,i,j+1) && is_valid_move(i,j,i,j+1)) {
                    *r1=i; *c1=j; *r2=i; *c2=j+1;
                    return 1;
                }
            }
        }
    }

    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS+1;j++) {

            if(!get_v_line(i,j)) {
                if(!creates_third_edge(i,j,i+1,j) && is_valid_move(i,j,i+1,j)) {
                    *r1=i; *c1=j; *r2=i+1; *c2=j;
                    return 1;
                }
            }
        }
    }

    return 0;
}

void bot_move(int *r1,int *c1,int *r2,int *c2) {

    static int initialized = 0;
    if(!initialized) {
        srand(time(NULL));
        initialized = 1;
    }

    if(try_complete_box(r1,c1,r2,c2)) return;

    if(try_safe_move(r1,c1,r2,c2)) return;

    do {
        *r1 = rand() % (ROWS + 1);
        *c1 = rand() % (COLS + 1);

        int dir = rand() % 2;

        if(dir == 0) {
            *r2 = *r1;
            *c2 = *c1 + 1;
        } else {
            *r2 = *r1 + 1;
            *c2 = *c1;
        }

    } while(!is_valid_move(*r1,*c1,*r2,*c2));
}
