#include <stdlib.h>
#include "board.h"

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

