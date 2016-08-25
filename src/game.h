/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : Hayden Warmington
 * Student Number   : s3486075
 * Course Code      : COSC1076
 * Program Code     : BH094
 * Start up code provided by Paul Miller
 **********************************************************************/

#include <time.h>
#include "shared.h"
#include "player.h"
#include "gameboard.h"


#ifndef GAME_H
#define GAME_H
#define DELIMS ","

struct player * play_game(PlayerType * first, PlayerType * second);
BOOLEAN apply_move(game_board board, int y, int x,enum cell player_token);
unsigned game_score(game_board board, enum cell player_token);
void swap_players(struct player ** first, struct player ** second);
void display_scene(game_board board, PlayerType *first, PlayerType* second,PlayerType* current);


#endif /* ifndef GAME_H */
