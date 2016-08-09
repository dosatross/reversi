/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
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
  fgets(first->name,NAMELEN,stdin);
  check_buffer_overflow(first->name);
  remove_newline(first->name);
  if (strlen(first->name)==0)
  {
    return FALSE; /*return false if empty*/
  }

}

BOOLEAN init_second_player(PlayerType * second, enum cell token)
{
  set_player_score(second,INITIAL_SCORE);
  set_player_token(second,token);
  /*set player name*/
  printf("Please enter the second player's name: ");
  fgets(second->name,NAMELEN,stdin);
  check_buffer_overflow(second->name);
  remove_newline(second->name);
  if (strlen(second->name)==0)
  {
    return FALSE; /*return false if empty*/
  }
}

/**
 * prompts the user for a comma-separate pair of coordinates for a move in the
 * game. Each move, if valid, must capture at least one enemy piece by
 * surrounding a sequence of one or more enemy pieces with two pieces of our
 * own: one being the new piece to be placed and the other a piece already
 * on the board. This function then validates that a valid move has been entered
 * calls the apply_move function to do the actual work of capturing pieces.
 **/
BOOLEAN make_move(struct player * human, game_board board)
{
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

void set_player_name(PlayerType * player)
{
  /*TODO*/
}

void set_player_token(PlayerType * player,enum cell token)
{
  player->token=token;
}

void set_player_score(PlayerType * player,unsigned score)
{
  player->score=score;
}
