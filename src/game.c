/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : Hayden Warmington
 * Student Number   : s3486075
 * Course Code      : COSC1076
 * Program Code     : BH094
 * Start up code provided by Paul Miller
 **********************************************************************/
#include "game.h"

struct player * play_game(PlayerType *first, PlayerType* second)
{
	game_board board;
	PlayerType * current, *other;

	if(initialise_players(first,second) == FALSE)
	{
		return NULL; /*return to main menu if name is empty*/
	}
	/*initialise player pointers*/
	if (first->token == RED)
	{
		current = first;
		other = second;
	}
	else
	{
		current = second;
		other = first;
	}

	init_game_board(board);
	init_cardinal_directions(cd);
	/*main game loop*/
	while(TRUE)
	{
		display_scene(board,first,second,current);
		/*return player with higher score if a player quits*/
		if (make_move(current,board) == FALSE)
		{
			if(current->score > other->score)
			{
				return current;
			}
			else if(current->score < other->score)
			{
				return other;
			}
			else
			{
				return NULL; /*return to main menu if buffer is empty*/
			}
		}
		else
		{
			/*update players scores and swap players*/
			current->score = game_score(board,current->token);
			other->score = game_score(board,other->token);
			swap_players(&current,&other);
		}
		
	}
}





/**
 * does the work of applying the move requested by the user to the game board.
 * It iterates over all the directions from the coordinate specified to see
 * whether there are any pieces that can be captured. If there are no pieces
 * that can be captured in any direction, it is an invalid move.
 **/
BOOLEAN apply_move(game_board board, int y, int x,enum cell player_token)
{
	unsigned element;
	unsigned elements_counter;
	unsigned i;
	Coordinate tokens_to_flip[MAX_TOKEN_FLIP];
	board[y-1][x-1] = player_token;

	/*init array to NULL*/
	for (i = 0; i < MAX_TOKEN_FLIP;i++)
	{
		tokens_to_flip[i].X = NULL_DIRECTION;
		tokens_to_flip[i].Y = NULL_DIRECTION;
	}

	element = 0;
	while(TRUE)
	{
		if(get_tokens_to_flip(board,y,x,player_token,element).X == NULL_DIRECTION)
		{
			break;
		}
		tokens_to_flip[element] = get_tokens_to_flip(board,y,x,player_token,element);
		element++;
	}

	elements_counter = 0;
	while(TRUE)
	{
		if(tokens_to_flip[elements_counter].X == NULL_DIRECTION && tokens_to_flip[elements_counter].Y == NULL_DIRECTION)
		{
			break;
		}
		elements_counter++;
	}
	for(i = 0;i < elements_counter;i++)
	{
		board[tokens_to_flip[i].Y][tokens_to_flip[i].X] = player_token;
	}
}


/**
 * simply count up how many locations contain the player_token
 * specified on the game_board.
 **/
unsigned game_score(game_board board, enum cell player_token)
{
	int i;
	int j;
	int count = 0;
	for (i = 1;i<=BOARD_HEIGHT;i++)
	{
		for (j = 1;j<=BOARD_WIDTH;j++)
		{
			if (board[i-1][j-1] == player_token)
			{
				count++;
			}
		}
	}
	return count;
}

/**
 * swap the two player pointers passed in so that first points to the player
 * pointer that originally contained the second player and vice versa.
 **/
void swap_players(struct player ** first, struct player ** second)
{
	PlayerType * temp;
	temp = *first;
	*first = *second;
	*second = temp;
}

void display_scene(game_board board, PlayerType *first, PlayerType* second, PlayerType *current)
{
	display_divider('=',80);
	printf("Player One's Details\n");
	display_divider('-',20);
	if(first->token == RED)
	{
		printf("Name: %s\tScore: %d\tToken Colour: %s0%s\n",first->name,first->score,COLOR_RED,COLOR_RESET);
		display_divider('-',80);
		printf("Player Two's Details\n");
		display_divider('-',20);
		printf("Name: %s\tScore: %d\tToken Colour: %s0%s\n",second->name,second->score,COLOR_BLUE,COLOR_RESET);
	}
	else
	{
		printf("Name: %s\tScore: %d\tToken Colour: %s0%s\n",first->name,first->score,COLOR_BLUE,COLOR_RESET);
		display_divider('-',80);
		printf("Player Two's Details\n");
		display_divider('-',20);
		printf("Name: %s\tScore: %d\tToken Colour: %s0%s\n",second->name,second->score,COLOR_RED,COLOR_RESET);
	}
	display_divider('-',80);
	display_board(board,first,second);
	printf("It is %s's turn.\n",current->name);
}
