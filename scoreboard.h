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
#include "player.h"
#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#define MAX_SCORES 10
typedef struct player score;

void init_scoreboard(score scoreboard[MAX_SCORES]);
BOOLEAN add_to_scoreboard(score scoreboard[MAX_SCORES], struct player * winner);
void display_scores(score scoreboard[MAX_SCORES]);
#endif /* ifndef SCOREBOARD_H */
