#ifndef PLAY_H_
#define PLAY_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "layout.h"


struct AI_move
{
    int x;
    int y;
    int score;
};

void setup_two_players(char p1, char p2);
int winner();
bool check_win(int p);
void play_two(int);
void newGame_play_two(int game);
bool StopGame(char, char, int);
int load_game();
void Restart_play();
struct AI_move AI_play(int);
void computer_paly();
bool help();
#endif