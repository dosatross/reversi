#include "shared.h"
#include <limits.h>
#ifndef UTILITY_H
#define UTILITY_H

/* the default line length for input / output */
#define LINELEN 80

/* the last two characters required in a string as returned from fgets */
#define EXTRACHARS 2

/* newline character required for I/O functions */
#define NEWLINE '\n'

void read_rest_of_line(void);
void display_menu_divider();
void check_buffer_overflow(char*);
void check_numeric(char*);
void remove_newline(char*);
#endif /* ifndef UTILITY_H */
