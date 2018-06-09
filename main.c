#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "play.h"


int main()
{
   struct AI_move all_possible_moves[1000000];
   int i;
   for (i =0 ; i < 1000000; i++)
        all_possible_moves[i].score = i;
    for ( i = 0; i < 1000000; i++)
    {
        printf("## : %d \n", all_possible_moves[i].score);
    }
    //this is the main loop of the game.
    while (1){
        int choice;
        printf("\t\t-----------------------\n");
        printf("\t\t| Wellcome to XO game |\n");
        printf("\t\t-----------------------\n\n");
        printf("1- Start new game\n");
        printf("2- Resume old game\n");
        printf("3- Help\n");
        printf("4- Exite\n\n");
        printf("Enter the number: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: {
                int c1 = -1;
                while(c1  != 3){
                    system("@cls||clear");
                    printf("1- Two players game.\n");
                    printf("2- One player game.\n");
                    printf("3- return.\n");
                    printf("4- Exite.\n");

                    printf("Enter your choice number: ");
                    scanf("%d", &c1);
                    while (c1 < 0 && c1 > 5){
                        printf("Invalid !\nEnter your choice number: ");
                        scanf("%d", &c1);
                    }
                    switch(c1){
                        case 1:{
                            newGame_play_two(2);
                        }
                
                        break;
                        case 2:{
                            newGame_play_two(1);

                        }
                        break;
                        case 4:
                            return 0;
                        break;
                        case 3:
                        // return case
                        break;
                        default:
                            printf("Invalid choice !\n");
                        break;
                    }
                }

            }
            break;

            case 2: {
                    system("@cls||clear");
                    Restart_play();
                    system("@cls||clear");
            }

            break;
         
            case 3: {
                    system("@cls||clear");
                    if (help())
                        return 0;
                    system("@cls||clear");

                }
            break;

            case 4:
                return 0; 
            break;

            default:
                system("@cls||clear");
                printf("Invalid choice !\n");
            break;
        }
    }   
    return 0;
}
