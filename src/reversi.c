/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 **********************************************************************/

#include "reversi.h"

/**
 * the hear of the program. The main() function in particular should
 * manage the main menu for the program.
 **/
int main(void)
{
  score scoreboard[MAX_SCORES];
  struct player first, second, *winner = NULL;
  init_scoreboard(scoreboard);
  display_menu_title();
  while(TRUE)
  {
    display_main_menu();
    parse_option(get_option());
  }
  return EXIT_SUCCESS;
}

/*menu functions*/
int get_option()
{
  char buffer[BUFFER_SIZE + FGETS_EXTRA_SPACES];
  fgets(buffer,BUFFER_SIZE + FGETS_EXTRA_SPACES,stdin);
  check_buffer_overflow(buffer);
  remove_newline(buffer); /*remove newline created by fgets*/
  check_numeric(buffer); /*checks input is numeric*/
  return strtol(buffer, NULL, 0); /* convert string to int and return*/
}
void parse_option(int option)
{
  switch (option)
  {
    case 1:
    {
      PlayerType first;
      PlayerType second;
      if(play_game(&first,&second) == NULL)
      {
        break;
      }
      break;
    }
    case 2:
    {
      display_high_scores();
      break;
    }
    case 3:
    {
      exit(0);
    }
    default:
    {
      display_invalid_input_message();
      break;
    }
  }
}


/*menu display functions*/

void display_main_menu()
{
  display_divider('-',MENU_DIVIDER_LENGTH);
  display_main_menu_options();
}

void display_menu_title()
{
  printf("Welcome to Reversi\n");
}

void display_invalid_input_message()
{
  display_divider('-',MENU_DIVIDER_LENGTH);
  printf("Error: Invalid Option\n");
}

void display_main_menu_options()
{
  printf("1. Play game\n");
  printf("2. Display High Scores\n");
  printf("3. Quit the program\n");
  printf("\n");
  printf("Please enter your choice: ");
}

void display_high_scores()
{
  display_high_score_header();
}

void display_high_score_header()
{
  display_divider('-',MENU_DIVIDER_LENGTH);
  printf("Name\t\t| Score\n");
  display_divider('-',MENU_DIVIDER_LENGTH);
}
