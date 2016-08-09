/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2016 Assignment #1
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 **********************************************************************/

#include "utility.h"

/**
 * function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != NEWLINE)
        ;
    clearerr(stdin);
}

void check_buffer_overflow(char* buffer)
{
  if(buffer[strlen(buffer)-1]!='\n')
  {
      printf("Error: buffer overflow\n\n");
      read_rest_of_line();
      return EXIT_FAILURE;
  }
}

void remove_newline(char* buffer)
{
  if(buffer[strlen(buffer)-1]=='\n')
  {
    buffer[strlen(buffer)-1]='\0';
  }
}

/*checks if is n*/
void check_numeric(char* buffer)
{
  char * end;
  strtol(buffer, &end, 0);
  if(*end)
  {
      printf("Error: data entered was not numeric.\n\n");
      end = NULL;
      return EXIT_FAILURE;
  }
}


void display_menu_divider()
{
  printf("-----------------------\n");
}
