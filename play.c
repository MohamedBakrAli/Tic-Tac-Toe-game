#include "play.h"

void setup_two_players(char p1, char p2){
	set_players(p1,p2);
	clean_board();
	cnt_play = 0;		
}

int Winnner(int p){
	if (p == 1){
		if (get_cnt_paly() == 9)
			return 0;
		else if (check_win(0))
			return 1;
		return -1;	
	} 
	else {
		if (get_cnt_paly() == 9)
			return 0;
		if (check_win(1))
			return 2;
		return -1;
	}
}

bool check_win(int p){
	char p_char = players[p];
	if ((board[0][0] == p_char && board[0][1] == p_char && board[0][2] == p_char) ||
		(board[1][0] == p_char && board[1][1] == p_char && board[1][2] == p_char) ||
		(board[2][0] == p_char && board[2][1] == p_char && board[2][2] == p_char) ||
		(board[0][0] == p_char && board[1][0] == p_char && board[2][0] == p_char) ||
		(board[0][1] == p_char && board[1][1] == p_char && board[2][1] == p_char) ||
		(board[0][2] == p_char && board[1][2] == p_char && board[2][2] == p_char) ||
		(board[0][0] == p_char && board[1][1] == p_char && board[2][2] == p_char) ||
		(board[0][2] == p_char && board[1][1] == p_char && board[2][0] == p_char))
		return true;
	return false;
}
void play_two(int game){

	int ro, col;
	int win = -1;
	print_board();
	while (win == -1){

		printf("First player[%c] : ",players[0]);
		scanf("%d",&ro);
		if (ro == -1){
			if (StopGame(players[0],players[1], game))
				break;
		}
		scanf("%d",&col);
		while (!set_cell(0,ro,col)){
			printf("Invalid cell !\nFirst player[%c] : ",players[0]);
			scanf("%d %d",&ro,&col);
		}
		print_board();
		win = Winnner(1);
		if (win == 0){
			printf("NO Winnner ^_^\n");
			continue;
		}
		else if (win == 1){
			printf("First player win ^_^\n");
			continue;
		}

		if (game == 2){
			printf("Second player[%c] : ",players[1]);
			scanf("%d",&ro);
			if (ro == -1){
				if (StopGame(players[1],players[0], game))
					break;
			}
			scanf("%d",&col);

			while (!set_cell(1,ro,col)){
				printf("Invalid cell !\nSecond player[%c] : ",players[1]);
				scanf("%d %d",&ro,&col);
			}
		}
		else {
			// COMPUTER 
			printf("computer !!!!\n");
			computer_paly();
		}
		
		print_board();	
		win = Winnner(2);
		if (win == 2){
			printf("Second player Win ^_^\n");		
		} 
		else if (win == 0){
			printf("NO Winnner ^_^\n");
		}

	}
	
 	
}

bool StopGame(char p1, char p2, int game){
	int c;
	while (1){
		printf("Stop Game :\n");
		printf("1- Save game. \n");
		printf("2- close without save.\n");
		printf("3- continue game. \n");
		printf("Enter number : ");
		scanf("%d", &c);
		switch(c){
			case 1: {
				char name[250];
				printf("Enter name : ");
				scanf("%s", name);
				// make the path of the save file 
				char path[250];
				strcpy(path,"save/");
				strcat(path,name);
				strcat(path,".txt");
				// write data to the save file 		
				FILE *out = fopen(path,"w");
				int i,j;
				for (i = 0; i < 3; i++){
					for (j = 0; j < 3; j++){
						if (board[i][j] == ' ')
							fprintf(out, "`\t");
						else 
							fprintf(out, "%c\t",board[i][j]);
					}
					fprintf(out, "\n");
				}
				fprintf(out, "%c\t%c\t%d\t%d",p1,p2,cnt_play,game);
				fclose(out);
				return true;
			}	

			break;
			case 2: {
				return true;
			}
			break;
			case 3: {
				return false;
			}
			break; 
			default :{
				printf("Inavlid choice !\n");
			}
			break;
		}
	}	

}
void newGame_play_two(int game){
	char p1,p2;
	bool flag = true;
	printf("Enter first player character : ");
	scanf (" %c", &p1);
	while(flag){
		printf("Enter second player character : ");
		scanf (" %c", &p2);    
		if (p1 == p2){
			printf("Invalid : choice different character !\n");
		}
		else {
			flag = false;
		}
	} 
	setup_two_players(p1,p2);
	play_two(game);
}
void Restart_play(){

	int game  = load_game();
	if (game == 2)
		play_two(2);
	else if (game == -1)
		return;
	else  
		play_two(1);
}
int load_game(){
	char path[250];
	int i,j;
	int game;
	char name [250];
	char c;
	FILE * in = NULL;
	while (in == NULL){
		printf("Enter the name of game or 1 to return:");
		scanf("%s",name);
		if (name[0] == '1' && name[1] == '\0')
			return -1;
		strcpy(path,"save/");
		strcat(path,name);
		strcat(path,".txt");
		in = fopen(path,"r");
		if (in == NULL)
			printf("Ther is no game with this name !\n");
		
	}
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			fscanf(in , " %c", &c);
			if (c == '`')
				board[i][j] = ' ';
			else 
				board[i][j] = c;
			
		}
	}
	fscanf(in, " %c %c", &players[0], &players[1]);
	fscanf(in, " %d %d",&cnt_play, &game);
	fclose(in);
	return game;
}



/*
	This will return the best possible move for the player
*/

struct AI_move AI_play(int player){
	struct AI_move temp;
	int i,j;
	if (Winnner(2) == 2){
		temp.score = 10;
		return temp;
	}
	else if (Winnner(2) == 0 || Winnner(1) == 0){
		temp.score = 0;
		return temp;
	}
	else if (Winnner(1) == 1){
		temp.score = -10;
		return temp;
	}
	
	struct AI_move all_possible_moves[1000];
	int cnt = 0;
	
	for (i = 0; i < 3; i ++){
		for (j = 0; j < 3; j++){
			if (board[i][j] == ' '){
				struct AI_move move;
				move.x  = i;
				move.y = j;

				set_cell(player-1, i, j);

				if (player == 2){

					//move.score = AI_play(1).score;					
				}
				else {
					
					//move.score = AI_play(2).score; 
				}
				
				all_possible_moves[cnt] = move;
				cnt ++;

				board[i][j] = ' ';
			}
		}
	}

	int bestmove  = 0;
	if (player == 2){
		int bestscore = -1000;
		for (i = 0; i < cnt; i++){
			if (all_possible_moves[i].score > bestscore){
				bestscore = all_possible_moves[i].score;
				bestmove = i;
			}
		} 
	}
	else {
		int bestscore = 1000;
		for (i = 0; i < cnt; i++){
			if (all_possible_moves[i].score < bestscore){
				bestscore = all_possible_moves[i].score;
				bestmove = i;
			}
		} 
	}
	return all_possible_moves[bestmove];
}

void computer_paly(){
	printf("hhh\n");
	struct AI_move best = AI_play(2);
	printf("gggggg\n" );
	printf("i : %d, j : %d \n",best.x, best.y );
	set_cell(1, best.x + 1, best.y + 1);
}

bool help(){
	printf("- this is two player game Xo.\n");
    printf("- You can play with another player or with computer.\n");
    printf("- to win you should make a row, column or diognal with you char (eg X,O ..) \n");
    printf("- the game have no winner if the board has no empty cell without winner.\n\n");
    printf("Enter 1  to return the previous screen or 2 to Exite: ");
    int c3 = -1;
    while (c3  != 1){
        scanf("%d", &c3);
        if (c3 == 2){
            return true;
        }
        else if (c3 != 1) {
            printf("Invalid choice !\n");
            printf("Enter 1  to return the previous screen or 2 to Exite: ");
        }
    }
    return false;
}