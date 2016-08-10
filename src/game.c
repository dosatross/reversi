/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 **********************************************************************/
#include "game.h"

/**
 * The heart of the game itself. You should do ALL initialisation required
 * for the game in here or call function required for that purpose. For example
 * both players should be initialised from here, you should seed the random
 * number generator, that kind of thing.
 *
 * Next, you should set the initial player - the initial player is the player
 * whose token was set by initialisation to RED.
 *
 * Next, you will need to manage the game loop in here. In each loop of the
 * game, you should display the game board, including player scores
 * display whose turn it is, etc in the format specified in the assignment
 * specification. Finally at the end of each turn you will calculate the score
 * for each player you will calculate their score and store it and then you
 * will need to swap the current player and other player
 * using the swap_player() function.
 *
 * A game will end when either player presses enter or ctrl-d on a newline.
 *
 * When you detect a request to end the game, you should do a final calculation
 * of the scores for the two players and return the player with the highest
 * score.
 **/
struct player * play_game(PlayerType *first, PlayerType* second)
{
	game_board board;
	enum cell token;
	Coordinate coordinate;
	char buffer[BUFFER_SIZE + FGETS_EXTRA_SPACES];
	BOOLEAN valid_move;
	PlayerType * current, *other, *winner;

	if(initialise_players(first,second) == FALSE)
	{
		return NULL; /*return to main menu if name is empty*/
	}
	/*initialise player pointers*/
	if (first->token == RED)
	{
		token = first->token;
		current = first;
		other = second;
	}
	else
	{
		token = second->token;
		current = second;
		other = first;
	}

	init_game_board(board);
	/*main game loop*/
	while(TRUE)
	{
		display_scene(board,first,second,current);
		valid_move = FALSE;
		while(valid_move == FALSE)
		{
			display_coordinate_prompt();
			/*get input*/
			fgets(buffer,BUFFER_SIZE + FGETS_EXTRA_SPACES,stdin);
			check_buffer_overflow(buffer);
			remove_newline(buffer);
			/*return player with higher score if a player quits*/
			if (strlen(buffer) == 0 || strcmp(buffer,"^D") == 0) /*TODO ctrl-D exit not working*/
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
				if (is_valid_move(buffer))
				{
					valid_move = TRUE;
					coordinate = parse_coordinate_buffer(buffer);
					apply_move(board, coordinate.Y, coordinate.X,current->token);
					/*update players score*/
					current->score = game_score(board,current->token);
					other->score = game_score(board,other->token);
					swap_players(&current,&other);
				}
				else
				{
					puts("Error: invalid coordinates.");
				}
			}
		}
	}
}

Coordinate parse_coordinate_buffer(char * buffer)
{
	char * tok;
	Coordinate coordinate;

	/*tokenise input*/
	tok = strtok(buffer, DELIMS);
	coordinate.X = (int) strtol(tok, NULL, 0);
	tok = strtok(NULL, DELIMS);
	coordinate.Y = (int) strtol(tok, NULL, 0);

	return coordinate;
}

BOOLEAN is_valid_move(char * buffer)
{
	return TRUE;
}

/**
 * does the work of applying the move requested by the user to the game board.
 * It iterates over all the directions from the coordinate specified to see
 * whether there are any pieces that can be captured. If there are no pieces
 * that can be captured in any direction, it is an invalid move.
 **/
BOOLEAN apply_move(game_board board, unsigned y, unsigned x,enum cell player_token)
{
	enum direction dir;
	unsigned captured_pieces = 0;
	board[y-1][x-1] = player_token;
}


/**
 * simply count up how many locations contain the player_token
 * specified on the game_board.
 **/
unsigned game_score(game_board board, enum cell player_token)
{
	int i;
	int j;
	unsigned count = 0;
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

void display_coordinate_prompt()
{
	printf("Please enter x and y coordinates separated by a comma for the piece you wish to place: ");
}
