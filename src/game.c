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
	init_cardinal_directions(cd);
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
				if (is_valid_move(board,buffer,current->token))
				{
					valid_move = TRUE;
					coordinate = parse_coordinate_buffer(buffer);
					apply_move(board, coordinate.Y, coordinate.X,current->token);
					/*update players score*/
					current->score = game_score(board,current->token);
					other->score = game_score(board,other->token);
					swap_players(&current,&other);
				}
			}
		}
	}
}

Coordinate parse_coordinate_buffer(char * buffer)
{
	char * tok;
	char buffer_copy[BUFFER_SIZE + FGETS_EXTRA_SPACES];
	Coordinate coordinate;

	strcpy(buffer_copy,buffer);
	/*tokenise input*/
	tok = strtok(buffer_copy, DELIMS);
	coordinate.X = (int) strtol(tok, NULL, 0);
	tok = strtok(NULL, DELIMS);
	coordinate.Y = (int) strtol(tok, NULL, 0);

	return coordinate;
}

BOOLEAN is_valid_move(game_board board,char * buffer,enum cell token)
{
	Coordinate coordinate;

	if (check_input(buffer) == FALSE)
	{
		return FALSE;
	}
	coordinate = parse_coordinate_buffer(buffer);
	if (get_tokens_to_flip(board,coordinate.Y,coordinate.X,token,0).X == NULL_DIRECTION)
	{
		return FALSE;
	}
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
	unsigned captured_pieces = 0;
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

BOOLEAN check_input(char * buffer)
{
	char * tok;
	int coordinate[DIMENSIONS];
	int numTok = 0;
	char buffer_copy[BUFFER_SIZE + FGETS_EXTRA_SPACES];

	strcpy(buffer_copy,buffer);
	tok = strtok(buffer_copy, DELIMS);
	while(tok!=NULL)
	{
		numTok++;
		if(numTok > DIMENSIONS)
		{
			printf("Error: invalid input; too many coordinates\n");
			return FALSE;
		}
		if (check_numeric(tok) == FALSE)
		{
			return FALSE;/*returns FALSE if input is not numeric*/
		}
		coordinate[numTok - 1] = (int) strtol(tok,NULL, 0);
		tok = strtok(NULL, DELIMS);
	}
	if (is_on_board(coordinate[0]-1,coordinate[1]-1) == FALSE)
	{
		printf("Error: invalid input; coordinate out of bounds\n");
		return FALSE;
	}
	return TRUE;
}

Coordinate get_tokens_to_flip(game_board board,unsigned y,unsigned x,enum cell token,unsigned element)
{
	int x_origin;
	int y_origin;
	int i;
	int elements_counter;
	enum cell other_token;
	Coordinate* tokens_to_flip = malloc(MAX_TOKEN_FLIP * sizeof(Coordinate));

	/*init array to NULL*/
	for (i = 0; i < MAX_TOKEN_FLIP;i++)
	{
		tokens_to_flip[i].X = NULL_DIRECTION;
		tokens_to_flip[i].Y = NULL_DIRECTION;
	}

	if(token==RED)
	{
		other_token = BLUE;
	}
	else
	{
		other_token = RED;
	}

	x -= 1;
	y -= 1;
	x_origin = x;
	y_origin = y;

	/*for each direction*/
	for (i=0;i<DIRECTIONS;i++)
	{
		x+= cd.a[i].X;
		y+= cd.a[i].Y;
		while(board[y][x] == other_token && is_on_board(y,x) == TRUE)
		{
			x+= cd.a[i].X;
			y+= cd.a[i].Y;
		}
		if(board[y][x] == token)
		{
			while (TRUE)
			{
				x -= cd.a[i].X;
				y -= cd.a[i].Y;
				if (x == x_origin && y == y_origin)
				{
					break;
				}
				/*append to tiles to flip*/
				elements_counter = 0;
				while(TRUE)
				{
					if(tokens_to_flip[elements_counter].X == NULL_DIRECTION && tokens_to_flip[elements_counter].Y == NULL_DIRECTION)
					{
						break;
					}
					elements_counter++;
				}
				tokens_to_flip[elements_counter].X = x;
				tokens_to_flip[elements_counter].Y = y;
			}
		}
		else
		{
			x = x_origin;
			y = y_origin;
		}
	}
	return tokens_to_flip[element];
}


BOOLEAN is_on_board(int y, int x)
{
	if (y > BOARD_HEIGHT || y <= 0 || x > BOARD_WIDTH || x <= 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
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
