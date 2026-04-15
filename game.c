#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "game.h"
#include "bot.h"

void start_game() {
    int r1, c1, r2, c2;
    char player = 'A';
    int mode;

    init_board();

    printf("Choose mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Bot\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    while (!is_game_over()) {
        print_board();

        if (mode == 2 && player == 'B') {
            bot_move(&r1, &c1, &r2, &c2);
            printf("Bot played: %d %d %d %d\n", r1, c1, r2, c2);
        } else {
            printf("Player %c's turn. Enter the row and column of the first dot (e.g., A0 -> 0 0) and second dot: \n", player);

            if (scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4) {
                printf("Invalid input!\n");
                while (getchar() != '\n');
                continue;
            }
        }

        int result = draw_line(r1, c1, r2, c2, player);

        if (result == -1) {
            printf("Invalid move! Try again.\n");
            continue;
        }

        if (result == 0) {
            player = (player == 'A') ? 'B' : 'A';
        }
    }

    print_board();

    int scoreA = get_score('A');
    int scoreB = get_score('B');

    printf("\nFinal Scores:\n");
    printf("A: %d\nB: %d\n", scoreA, scoreB);

    if(scoreA > scoreB) printf("Player A wins!\n");
    else if(scoreB > scoreA) printf("Player B wins!\n");
    else printf("Draw!\n");
}
