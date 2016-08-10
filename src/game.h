/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 **********************************************************************/
#include <time.h>
#include "shared.h"
#include "player.h"
#include "gameboard.h"


#ifndef GAME_H
#define GAME_H
#define BUFFER_SIZE 10
#define FGETS_EXTRA_SPACES 2
#define DELIMS ","

struct player * play_game(PlayerType * first, PlayerType * second);
BOOLEAN apply_move(game_board board, unsigned y, unsigned x,
                   enum cell player_token);
unsigned game_score(game_board board, enum cell player_token);
void swap_players(struct player ** first, struct player ** second);
void display_scene(game_board board, PlayerType *first, PlayerType* second,PlayerType* current);
Coordinate parse_coordinate_buffer(char *);
BOOLEAN is_valid_move(char *);
void display_coordinate_prompt();

#endif /* ifndef GAME_H */
