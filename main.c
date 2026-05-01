#include "game.h"
#include <stdio.h>
#include "network.h"
int main() {
int c;
printf("==============================\n");
printf("     DOTS AND BOXES GAME\n");
printf("==============================\n");
printf("Team Members:\n");
printf("-Majd Al Halabi\n");
printf("-Lea Tass\n");
printf("==============================\n");
printf("\nChoose Mode:\n");
printf("1. Local Game\n");
printf("2. Play with Bot\n");
printf("3. Host Game\n");
printf("4. Join Game\n");

    scanf("%d",&c);

    if(c==1){
        play_game();
    }
    else if(c==2){
        play_with_bot();
    }
    else if(c==3){
        play_network_host();
    }
    else if(c==4){
        char ip[50];
        printf("Enter Server IP: ");
        scanf("%s",ip);
        play_network_client(ip);
    }

    return 0;
}
