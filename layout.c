#include "layout.h"

/*
	this function to select the two chars of the two players
*/
void set_players(char p1, char p2){
	players[0] = p1;
	players[1] = p2;
}
/*
	this function print the game board to the console screen
*/
void print_board(){
	int i,j;
	system("@cls||clear");
	printf("\t\t     -----------------------\n");
	printf("\t\t     | Wellcome to XO game |\n");
	printf("\t\t     -----------------------\n\n");
    printf("\t\t        1       2       3   \n");
    for (i = 0; i < 3; i++){

        printf("\t\t    -------------------------\n\t\t%d   ", i+1);
        for (j = 0; j < 3; j++){
            printf("|   %c   ",board[i][j]);
        }
        printf("|\n");
    }
    printf("\t\t    -------------------------\n\n");
    printf("Enter (row column) or -1 to stop \n");
}
/*
	this function clear the board from the prevouse plays.
	I use it to clear the board to start new game.
*/
void clean_board(){
	int i, j;
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++)
			board[i][j] = ' ';
	}
}
/*
	set the player char in the cell he want to move to	
*/
bool set_cell(int player, int i, int j){
	if ( i > 0 && i < 4 && j > 0 && j < 4){
		if (board[i-1][j-1] == ' '){
			board[i-1][j-1] = players[player];
			cnt_play ++;
			return true;	
		}
	}	
	return false;
}

/*
	get the number of player that set this cell or -1 if it's empty
*/
int get_cell(int i, int j){
	char cell = board[i][j];
	if (cell == ' ')
		return -1;
	else if (cell == players[0])
		return 1;
	else 
		return 2;
}

/* return the number of players to the two player*/
int get_cnt_paly(){
	return cnt_play;
}