#ifndef LAYOUT_H_   /* Include guard */
#define LAYOUT_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
char board[3][3];
char players[2];
int cnt_play;

void set_players(char, char);
void print_board();
void clean_board();

bool set_cell(int, int, int);
int get_cell(int, int);

int get_cnt_paly();

#endif