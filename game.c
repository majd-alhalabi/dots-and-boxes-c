#include <stdio.h>
#include "board.h"
#include "bot.h"
#include "network.h"

int sock;

void play_game(){
    init_board();
    char player='A';
    int r1,c1,r2,c2;

    while(!is_game_over()){
        print_board();

        printf("\n------------------------------------\n");
        printf("Player %c's turn\n", player);
        printf("Enter move (r1 c1 r2 c2): ");
        
        if(scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4){
            printf("Invalid input! Please enter 4 integers.\n");
            while(getchar() != '\n');
            continue;
        }

        if(!is_valid_move(r1,c1,r2,c2)){
            printf("Invalid move! Try again.\n");
            continue;
        }

        int boxes = draw_line(r1,c1,r2,c2,player);
        
        printf("\n*******************************\n");
        printf("Player A score: %d\n", get_score('A'));
        printf("Player B score: %d\n", get_score('B'));
        printf("*******************************\n\n");
        
        if(boxes == 0){
            player = (player == 'A') ? 'B' : 'A';
        }
    }

    print_board();
    
    int scoreA = get_score('A');
    int scoreB = get_score('B');
    
    printf("\n====== FINAL SCORES ======\n");
    printf("Player A: %d\n", scoreA);
    printf("Player B: %d\n", scoreB);
    printf("====== THE WINNER ======\n");
    
    if(scoreA > scoreB){
        printf("Player A wins!\n");
    }else if(scoreB > scoreA){
        printf("Player B wins!\n");
    }else{
        printf("It's a draw!\n");
    }
}

void play_with_bot(){
    init_board();
    char player='A';
    int r1,c1,r2,c2;

    while(!is_game_over()){
        print_board();

        if(player=='A'){
            printf("\n------------------------------------\n");
            printf("Player %c's turn\n", player);
            printf("Enter move (r1 c1 r2 c2): ");
            
            if(scanf("%d %d %d %d", &r1, &c1, &r2, &c2) != 4){
                printf("Invalid input! Please enter 4 integers.\n");
                while(getchar() != '\n');
                continue;
            }
        }else{
            bot_move(&r1,&c1,&r2,&c2);

            printf("\n====================================\n");
            printf("Bot played: %d %d %d %d\n", r1, c1, r2, c2);
            printf("====================================\n\n");
        }

        if(!is_valid_move(r1,c1,r2,c2)){
            if(player == 'A'){
                printf("Invalid move! Try again.\n");
            }
            continue;
        }

        int boxes = draw_line(r1,c1,r2,c2,player);
        
        printf("\n*******************************\n");
        printf("Player A score: %d\n", get_score('A'));
        printf("Player B score: %d\n", get_score('B'));
        printf("*******************************\n\n");
        
        if(boxes == 0){
            player = (player == 'A') ? 'B' : 'A';
        }
    }

    print_board();
    
    int scoreA = get_score('A');
    int scoreB = get_score('B');
    
    printf("\n====== FINAL SCORES ======\n");
    printf("Player A: %d\n", scoreA);
    printf("Player B: %d\n", scoreB);
    printf("====== THE WINNER ======\n");
    
    if(scoreA > scoreB){
        printf("Player A wins!\n");
    }else if(scoreB > scoreA){
        printf("Bot wins!\n");
    }else{
        printf("It's a draw!\n");
    }
}

void play_network_host(){
    int server = start_server();
    sock = accept_client(server);

    init_board();
    char player = 'A';
    Move m;

    while(!is_game_over()){
        print_board();

        if(player == 'A'){
            printf("\n------------------------------------\n");
            printf("Player %c's turn\n", player);
            printf("Enter move (r1 c1 r2 c2): ");
            
            if(scanf("%d %d %d %d", &m.r1, &m.c1, &m.r2, &m.c2) != 4){
                printf("Invalid input! Please enter 4 integers.\n");
                while(getchar() != '\n');
                continue;
            }

            if(!is_valid_move(m.r1, m.c1, m.r2, m.c2)){
                printf("Invalid move! Try again.\n");
                continue;
            }

            int boxes = draw_line(m.r1, m.c1, m.r2, m.c2, 'A');
            send_move(sock, m);
            
            printf("\n*******************************\n");
            printf("Player A score: %d\n", get_score('A'));
            printf("Player B score: %d\n", get_score('B'));
            printf("*******************************\n\n");
            
            if(boxes == 0){
                player = 'B';
            }
        }else{
            printf("\n====================================\n");
            printf("Waiting for opponent's move...\n");
            
            if(receive_move(sock, &m) <= 0){
                printf("Connection error! Opponent disconnected.\n");
                break;
            }
            
            printf("Opponent played: %d %d %d %d\n", m.r1, m.c1, m.r2, m.c2);
            printf("====================================\n\n");

            int boxes = draw_line(m.r1, m.c1, m.r2, m.c2, 'B');
            
            printf("\n*******************************\n");
            printf("Player A score: %d\n", get_score('A'));
            printf("Player B score: %d\n", get_score('B'));
            printf("*******************************\n\n");
            
            if(boxes == 0){
                player = 'A';
            }
        }
    }

    print_board();
    
    int scoreA = get_score('A');
    int scoreB = get_score('B');
    
    printf("\n====== FINAL SCORES ======\n");
    printf("Player A: %d\n", scoreA);
    printf("Player B: %d\n", scoreB);
    printf("====== THE WINNER ======\n");
    
    if(scoreA > scoreB){
        printf("Player A wins!\n");
    }else if(scoreB > scoreA){
        printf("Player B wins!\n");
    }else{
        printf("It's a draw!\n");
    }
    
    close(sock);
    close(server);
}

void play_network_client(const char* ip){
    sock = connect_to_server(ip);
    if(sock < 0){
        printf("Failed to connect to server!\n");
        return;
    }

    init_board();
    char player = 'A';
    Move m;

    while(!is_game_over()){
        print_board();

        if(player == 'B'){
            printf("\n------------------------------------\n");
            printf("Player %c's turn\n", player);
            printf("Enter move (r1 c1 r2 c2): ");
            
            if(scanf("%d %d %d %d", &m.r1, &m.c1, &m.r2, &m.c2) != 4){
                printf("Invalid input! Please enter 4 integers.\n");
                while(getchar() != '\n');
                continue;
            }

            if(!is_valid_move(m.r1, m.c1, m.r2, m.c2)){
                printf("Invalid move! Try again.\n");
                continue;
            }

            int boxes = draw_line(m.r1, m.c1, m.r2, m.c2, 'B');
            send_move(sock, m);
            
            printf("\n*******************************\n");
            printf("Player A score: %d\n", get_score('A'));
            printf("Player B score: %d\n", get_score('B'));
            printf("*******************************\n\n");
            
            if(boxes == 0){
                player = 'A';
            }
        }else{
            printf("\n====================================\n");
            printf("Waiting for opponent's move...\n");
            
            if(receive_move(sock, &m) <= 0){
                printf("Connection error! Opponent disconnected.\n");
                break;
            }
            
            printf("Opponent played: %d %d %d %d\n", m.r1, m.c1, m.r2, m.c2);
            printf("====================================\n\n");

            int boxes = draw_line(m.r1, m.c1, m.r2, m.c2, 'A');
            
            printf("\n*******************************\n");
            printf("Player A score: %d\n", get_score('A'));
            printf("Player B score: %d\n", get_score('B'));
            printf("*******************************\n\n");
            
            if(boxes == 0){
                player = 'B';
            }
        }
    }

    print_board();
    
    int scoreA = get_score('A');
    int scoreB = get_score('B');
    
    printf("\n====== FINAL SCORES ======\n");
    printf("Player A: %d\n", scoreA);
    printf("Player B: %d\n", scoreB);
    printf("====== THE WINNER ======\n");
    
    if(scoreA > scoreB){
        printf("Player A wins!\n");
    }else if(scoreB > scoreA){
        printf("Player B wins!\n");
    }else{
        printf("It's a draw!\n");
    }
    
    close(sock);
}

