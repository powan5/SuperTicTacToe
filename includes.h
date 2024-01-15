#include <stdlib.h>    // Standard Library: General purpose functions, including dynamic memory allocation and random number generation.
#include <stdio.h>     // Standard Input/Output: Functions for reading and writing to the console.
#include <stdbool.h>   // Standard Boolean: Defines the bool type and true/false constants.
#include <string.h>    // String Library: Functions for manipulating strings.
#include <ctype.h>     // Character Type: Functions for character handling, like checking if a character is alphanumeric.
#include <unistd.h>    // Unix Standard: Functions related to system calls, including sleep().
#include <time.h>      // Time Library: Functions for working with date and time.
#include <float.h>     // Floating Point Library: Functions for floating point math.
#include <math.h>      // Math Library: Functions for mathematical operations.

/* Terminal stuff (UI) */
#define CLEAR_TERMINAL "\033[2J\033[1;1H"

#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"

/* Generally used constants */
#define ROW 3
#define COLUMN 3