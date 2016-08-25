/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : Hayden Warmington
 * Student Number   : s3486075
 * Course Code      : COSC1076
 * Program Code     : BH094
 * Start up code provided by Paul Miller
 **********************************************************************/

#include "shared.h"
#include "gameboard.h"
#include "utility.h"

#ifndef PLAYER_H
#define PLAYER_H
/* the maximum length of a player name */
#define NAMELEN 20
#define INITIAL_SCORE 0
/* the number of characters allowed when the user is entering the coordinates
 * for a game
 */

/* what are the attributes of a player? They have a score, a token (either BLUE
 * or RED), and a score
 */
typedef struct player
{
    char name[NAMELEN + 1];
    enum cell token;
    unsigned score;
} PlayerType;

BOOLEAN initialise_players(PlayerType *first, PlayerType* second);
BOOLEAN init_first_player(PlayerType * first, enum cell token);
BOOLEAN init_second_player(PlayerType * second, enum cell token);
BOOLEAN make_move(PlayerType * player, game_board board);

Coordinate parse_coordinate_buffer(char *);
BOOLEAN is_valid_move(game_board,char *,enum cell token);
void display_coordinate_prompt();
BOOLEAN check_input(char * buffer);
Coordinate get_tokens_to_flip(game_board board,int y,int x,enum cell token,unsigned element);
BOOLEAN is_on_board(int, int);

void set_player_name(PlayerType * player);
void set_player_token(PlayerType * player,enum cell token);
void set_player_score(PlayerType * player,unsigned score);

#endif /* ifndef PLAYER_H */
