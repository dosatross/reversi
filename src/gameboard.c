/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 **********************************************************************/
#include "gameboard.h"
#include "player.h"

/**
 * initialise the game board to be consistent with the screenshot provided
 * in your assignment specification.
 *
 * All squares should be initialised to be blank other than the four
 * squares in the middle of the board. In that case they are initialised to
 * appropriate colored tokens
 **/
void init_game_board(game_board board)
{
	int i;
	int j;
	for(i = 0;i < BOARD_HEIGHT;i++)
	{
		for(j = 0;j < BOARD_WIDTH;j++)
		{
			board[i][j] = BLANK;
		}
	}
	board[3][3] = RED;
	board[4][4] = RED;
	board[3][4] = BLUE;
	board[4][3] = BLUE;
}

/**
 * display the board as specified in the assignment specification. You should
 * make every effort to create a board consistent with the screenshots in the
 * assignment specification.
 **/
void display_board(game_board board, struct player * first,
                   struct player * second)
{
	display_board_column_index();
	display_divider('=',BOARD_DIVIDER_LENGTH);
	display_board_body(board);
}

void display_board_body(game_board board)
{
	int i;
	int j;
	for (i = 1;i<=BOARD_HEIGHT;i++)
	{
		printf(" %d |",i);
		for (j = 1;j<=BOARD_WIDTH;j++)
		{
			switch(board[i-1][j-1])
			{
				case BLANK:
				{
					printf("   |",0);
					break;
				}
				case RED:
				{
					printf(" %s%d%s |",COLOR_RED,0,COLOR_RESET);
					break;
				}
				case BLUE:
				{
					printf(" %s%d%s |",COLOR_BLUE,0,COLOR_RESET);
					break;
				}
				default:
				{
					break;
				}
			}
		}
		printf("\n");
		display_divider('-',BOARD_DIVIDER_LENGTH);
	}
}

void display_board_column_index()
{
	int i;
	printf("    ");
	for (i = 1;i<=BOARD_WIDTH;i++)
	{
		printf(" %i  ",i);
	}
	printf("\n");
}
