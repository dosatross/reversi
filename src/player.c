/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : Hayden Warmington
 * Student Number   : s3486075
 * Course Code      : COSC1076
 * Program Code     : BH094
 * Start up code provided by Paul Miller
 **********************************************************************/
#include "player.h"
#include "game.h"

/**
 * These two functions initialise the player structure at the beginning of the
 * game. In both cases, you should initialise the whole structure to known safe
 * values and then prompt the user for their name. In the init_first_player()
 * function you should then select a color at random for this player using the
 * rand() function. This token should be assigned to the first player's token and
 * also returned via the token pointer. In init_second_player() you should just
 * test the value of token and assign the opposite color to the second player.
 **/



BOOLEAN init_first_player(PlayerType * first, enum cell token)
{
  set_player_score(first,INITIAL_SCORE);
  set_player_token(first,token);
  /*set player name*/
  printf("Please enter the first player's name: ");
  if (fgets(first->name,NAMELEN,stdin) == NULL)
  {
    printf("\n");
    return FALSE; /*return false if ctrl - d*/
  }
  check_buffer_overflow(first->name);
  remove_newline(first->name);
  if (strlen(first->name)==0)
  {
    return FALSE; /*return false if empty*/
  }
  return TRUE;

}

BOOLEAN init_second_player(PlayerType * second, enum cell token)
{
  set_player_score(second,INITIAL_SCORE);
  set_player_token(second,token);
  /*set player name*/
  printf("Please enter the second player's name: ");
  if (fgets(second->name,NAMELEN,stdin) == NULL)
  {
    printf("\n");
    return FALSE; /*return false if ctrl - d*/
  }
  check_buffer_overflow(second->name);
  remove_newline(second->name);
  if (strlen(second->name)==0)
  {
    return FALSE; /*return false if empty*/
  }
  return TRUE;
}

/**
 * prompts the user for a comma-separate pair of coordinates for a move in the
 * game. Each move, if valid, must capture at least one enemy piece by
 * surrounding a sequence of one or more enemy pieces with two pieces of our
 * own: one being the new piece to be placed and the other a piece already
 * on the board. This function then validates that a valid move has been entered
 * calls the apply_move function to do the actual work of capturing pieces.
 **/
BOOLEAN make_move(struct player * current, game_board board)
{
  char buffer[BUFFER_SIZE + FGETS_EXTRA_SPACES];
  BOOLEAN valid_move;
  Coordinate coordinate;

  valid_move = FALSE;
  while(valid_move == FALSE)
  {
    display_coordinate_prompt();
    /*get input*/
    if (fgets(buffer,BUFFER_SIZE + FGETS_EXTRA_SPACES,stdin) == NULL)
    {
      {
        printf("\n");
        return FALSE; /*return false if ctrl - d*/
      }
    }
    check_buffer_overflow(buffer);
    remove_newline(buffer);
    if (strlen(buffer) == 0)
    {
      return FALSE;
    }

    if (is_valid_move(board,buffer,current->token))
    {
      valid_move = TRUE;
      coordinate = parse_coordinate_buffer(buffer);
      apply_move(board, coordinate.Y, coordinate.X,current->token);
    }

  }
  return TRUE;
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
    printf("Error: invalid move\n");
    return FALSE;
  }
  return TRUE;
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
  if (is_on_board(coordinate[0],coordinate[1]) == FALSE)
  {
    printf("Error: invalid input; coordinate out of bounds\n");
    return FALSE;
  }
  return TRUE;
}

Coordinate get_tokens_to_flip(game_board board,int y,int x,enum cell token,unsigned element)
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
    while(board[y][x] == other_token && is_on_board(y + 1,x + 1) == TRUE)
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

BOOLEAN initialise_players(PlayerType *first, PlayerType* second)
{
  int randomNumber;
  srand(time(NULL)); /*seed random number*/
  randomNumber = (rand()%2); /*random number between 0 and 1*/
	if (randomNumber == 0)
	{
    if(init_first_player(first,RED) == FALSE)
    {
      return FALSE;
    }
    if(init_second_player(second,BLUE) == FALSE)
    {
      return FALSE;
    }
	}
	else
	{
    if(init_first_player(first,BLUE) == FALSE)
    {
      return FALSE;
    }
    if(init_second_player(second,RED) == FALSE)
    {
      return FALSE;
    }
	}
  return TRUE;
}

void set_player_token(PlayerType * player,enum cell token)
{
  player->token=token;
}

void set_player_score(PlayerType * player,unsigned score)
{
  player->score=score;
}


void display_coordinate_prompt()
{
  printf("Please enter x and y coordinates separated by a comma for the piece you wish to place: ");
}