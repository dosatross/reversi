/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 **********************************************************************/
#include "shared.h"
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

/* how much space is required to display a column on the game board ? */
#define COLUMN_WIDTH 4
/* how tall is the game board - 8 places high */
#define BOARD_HEIGHT 8
/* how wide is the game board ? */
#define BOARD_WIDTH BOARD_HEIGHT
#define DIRECTIONS 8
#define NEGATIVE_DIRECTION -1
#define POSITIVE_DIRECTION 1
#define ZERO_DIRECTION 0
#define NULL_DIRECTION (BOARD_HEIGHT + 1)
#define MAX_TOKEN_FLIP (BOARD_HEIGHT*BOARD_HEIGHT) /*arbitrary*/
#define BOARD_DIVIDER_LENGTH ((BOARD_WIDTH + 1)*COLUMN_WIDTH)
#define DIMENSIONS 2

/* forwards declaration of a struct player. This means that the compiler knows
 * that such a datastructure will be available but it does not what it contains
 * and so we can have pointers to a player but we don't know how big it is or
 * what it contains.
 */
struct player;
/* all the directions that we can capture pieces in leaving from this direction
 */

typedef struct direction
{
  int X;
  int Y;
} Direction;

typedef struct coordinate
{
  int X;
  int Y;
} Coordinate;

union cardinal_direction
{
  Direction a[DIRECTIONS];
  struct
  {
    Direction east;
  	Direction west;
  	Direction north;
  	Direction south;
  	Direction north_east;
  	Direction north_west;
  	Direction south_east;
  	Direction south_west;
  } s;
} cd;

/* type definition of a game_board. It is just a 2-dimensional array */
typedef enum cell game_board[BOARD_HEIGHT][BOARD_WIDTH];

void init_game_board(game_board board);
void init_cardinal_directions();
void display_board(game_board board, struct player * first,struct player * second);
void display_board_body(game_board);
void display_board_column_index();
#endif /* ifndef GAMEBOARD_H */
