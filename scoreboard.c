/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 **********************************************************************/

#include "scoreboard.h"

/**
 * initalise the scoreboard so that the scores for each element of the array
 * is set to 0.
 **/
void init_scoreboard(score scoreboard[MAX_SCORES])
{
  int i;
  for(i = 0;i < MAX_SCORES;i++)
  {
    scoreboard[i].score = 0;
    strcpy(scoreboard[i].name,"");
  }
}


/**
 * insert the top scorer from the last game played in sorted order according
 * to their score
 **/
BOOLEAN add_to_scoreboard(score scoreboard[MAX_SCORES], struct player * winner)
{

}

/**
 * display the scores in the scoreboard according to their order. Your output
 * should match that provided in the assignment specification.
 **/
void display_scores(score scoreboard[MAX_SCORES])
{

}
