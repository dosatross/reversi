/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : Hayden Warmington
 * Student Number   : s3486075
 * Course Code      : COSC1076
 * Program Code     : Adv Prog Techniques
 * Start up code provided by Paul Miller
 **********************************************************************/
#include "shared.h"
#include "player.h"
#include "game.h"
#include "scoreboard.h"
#include "utility.h"

#ifndef REVERSI_H
#define REVERSI_H
#define MENU_DIVIDER_LENGTH 20

int get_option();
void parse_option(int);
void initialise_game();
/*menu display*/
void display_main_menu();
void display_menu_title();
void display_main_menu_options();
void display_high_scores();
void display_high_score_header();
void display_invalid_input_message();

#endif
