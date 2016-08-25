/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : Hayden Warmington
 * Student Number   : s3486075
 * Course Code      : COSC1076
 * Program Code     : BH094
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
  int i;
  int j;
  for(i = 0;i < MAX_SCORES;i++)
  {
    if(scoreboard[i].score <= winner->score)
    {
      /*shift scores down*/
      for(j = (MAX_SCORES - 1);j > i;j--)
      {
        scoreboard[j].score = scoreboard[j - 1].score;
        strcpy(scoreboard[j].name,scoreboard[j - 1].name);
      }
      scoreboard[i].score = winner->score;
      strcpy(scoreboard[i].name,winner->name);
      break;
    }
  }
  return TRUE;
}

/**
 * display the scores in the scoreboard according to their order. Your output
 * should match that provided in the assignment specification.
 **/
void display_scores(score scoreboard[MAX_SCORES])
{
  int i;
  for(i = 0;i < MAX_SCORES;i++)
  {
    if(scoreboard[i].score != 0)
    {
      printf("%s\t\t| %d\n",scoreboard[i].name,scoreboard[i].score);
    }
  }
}
