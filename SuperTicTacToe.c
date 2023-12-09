/**
 * @brief Program to play Super Tic-Tac-Toe, a variation of tic-tac-toe where players need to complete a grid in order to claim a square of the main grid ('super grid')
 * 
 * @author Powan
 * @version Beta 1.0.3
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
// while (getchar() != '\n');  // Buffer clear (if usage of strings)

/*-- Constants & Types --*/

#define ROW 3
#define COLUMN 3
#define P1 1
#define P2 2

typedef struct Grid { char grid[ROW][COLUMN]; };

typedef char List[ROW][COLUMN];
const List letters = {{'A','B','C'}, {'D','E','F'}, {'G','H','I'}};

typedef char * gridBlocks[3][9];    

/*-- Prototypes initialisation --*/

/**
 * @brief Prints the initial welcome message.
 */
void welcome();

/**
 * @brief Initialise "the super grid's grids values with 'Z'.
 * 
 * @param superGrid Game's grid.
 */
void initSuperGrid(struct Grid superGrid[ROW][COLUMN]);

/**
 * @brief Asks the User for a CHAR input in order to choose where to play in the 'super grid'.
 * 
 * @param adrInput adress of the input variable.
 */
void inputWhichGrid(char *adrInput);

/**
 * @brief Asks the User for an INT input in order to choose where to play in the grid inside the 'super grid'.
 * 
 * @param adrInput Adress of the input variable.
 */
void inputWhichSquare(char *adrInput);

/**
 * @brief Checks if the given grid inside 'super grid' is complete.
 * 
 * @param superGrid Game's grid.
 * @param letter Letter of the grid to check, gives the index of said grid.
 * @return 1 if Player1 has finished it, 2 if Player2 did, 0 otherwise.
 */
int gridComplete(struct Grid superGrid[ROW][COLUMN], char letter);

/**
 * @brief Checks if the 'super grid' is completed, so if the game finished.
 * 
 * @param superGrid Game's grid.
 * @return 1 if Player1 has won, 2 if Player2 did, 0 otherwise.
 */
int superGridComplete(struct Grid superGrid[ROW][COLUMN]);

/**
 * @brief Prints the game's grid in the terminal.
 * 
 * @param superGrid Game's grid.
 */
void PrintGrid(struct Grid superGrid[ROW][COLUMN]);

int main()
{
    /*-- Variables --*/

    struct Grid grid;
    struct Grid superGrid[ROW][COLUMN];
    int temp;

    welcome();

    /*-- Inputs --*/

    initSuperGrid(superGrid);


    /*-- Printing of the grid --*/

    printf("\033[2J\033[1;1H"); // Clears output terminal
    // PrintGrid(superGrid);
    scanf("%d", &temp);

    return EXIT_SUCCESS;
}

/*-- Prototypes definitions --*/

/**
 * @brief Initialise 'the super grid's grids values with 'Z'.
 * 
 * @param superGrid Game's grid.
 */
void initSuperGrid(struct Grid superGrid[ROW][COLUMN]) //Finished
{
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COLUMN; col++) {
            for (int gridRow = 0; gridRow < ROW; gridRow++) {
                for (int gridCol = 0; gridCol < COLUMN; gridCol++) {
                    superGrid[row][col].grid[gridRow][gridCol] = '.';
                }
            }
        }
    }
}

/**
 * @brief Prints the game's grid in the terminal.
 * 
 * @param superGrid Game's grid.
 */
void PrintGrid(struct Grid superGrid[ROW][COLUMN]) // Finished, but kinda broken for some unknown reason
{

    /*-- Output template --*/

    gridBlocks LETTERS = {{
        "| %c   1   2   3   %c ",
        "|   +---+---+---+   ",
        "| 1 | %c | %c | %c | 1 ",
        "|   +---+---+---+   ",
        "| 2 | %c | %c | %c | 2 ",
        "|   +---+---+---+   ",
        "| 3 | %c | %c | %c | 3 ",
        "|   +---+---+---+   ",
        "| %c   1   2   3   %c "},
        {
        "|                   ",
        "|                   ",
        "|       \\   /       ",
        "|        \\ /        ",
        "|         X         ",
        "|        / \\        ",
        "|       /   \\       ",
        "|                   ",
        "|                   "},
        {
        "|                   ",
        "|                   ",
        "|     /-------\\     ",
        "|     |       |     ",
        "|     |       |     ",
        "|     |       |     ",
        "|     \\-------/     ",
        "|                   ",
        "|                   "}
        };


    /**-- Main loop --*/

    /* Divides the 'super grid' in rows and columns */
    for (int superRow = 0; superRow < ROW; superRow++)
    {
        printf("+-------------------+-------------------+-------------------+\n"); /* Dividers for the 'super grid' */
        int tinyRowIndex = 0; /* Counter to divide each tinyRow in 9 lines */

        for (int superCol = 0; superCol < COLUMN; superCol++)
        {
            /* Divides each square of the 'super grid' in sets of rows and columns */
            for (int tinyRow = 0; tinyRow < ROW; tinyRow++)
            {
                for (int tinyCol = 0; tinyCol < COLUMN; tinyCol++)
                {
                    char printableLine[20]; /* Creates a printable line for template (to be able to utilize the '%c') */

                    switch (gridComplete(superGrid, letters[superRow][superCol])) /* Checks if a player has won a square of the 'super grid' or not */
                    {

                    /* Prints the square if a player has won it */
                    case P1:
                        printf("%s", LETTERS[P1][tinyRowIndex]);
                        break;
                    
                    case P2:
                        printf("%s", LETTERS[P2][tinyRowIndex]);
                        break;

                    /* Prints the square if neither of the players has won it */
                    default:
                        printf("%s", LETTERS[P2][tinyRowIndex]);
                        //if (tinyRowIndex == 0 || tinyRowIndex == 8) /* "| %c   1   2   3   %c " */
                        //{
                        //    sprintf(printableLine, LETTERS[0][tinyRowIndex], letters[superRow][tinyCol], letters[superRow][tinyCol]);
                        //    printf("%s", printableLine);
                        //    char printableLine[20] = "";
                        //    break; 
                        //}
                        //else if (tinyRowIndex == 1 || tinyRowIndex == 3 || tinyRowIndex == 5 || tinyRowIndex == 7) /* "|   +---+---+---+   " */
                        //{
                        //    printf("%s", LETTERS[0][tinyRowIndex]); 
                        //    break; 
                        //}
                        //else /* "| [nb] | %c | %c | %c | [nb] " */
                        //{
                        //    sprintf(printableLine, LETTERS[0][tinyRowIndex], superGrid[superRow][superCol].grid[tinyRow][tinyRowIndex%3], superGrid[superRow][superCol].grid[tinyRow][tinyRowIndex%3], superGrid[superRow][superCol].grid[tinyRow][tinyRowIndex%3]);
                        //    printf("%s", printableLine); 
                        //    char printableLine[20] = "";
                        //    break; 
                        //}
                        //break;
                    }
                }
                /* end of line */
                tinyRowIndex++;
                printf("|\n"); 
            }
        }
    }
    printf("+-------------------+-------------------+-------------------+\n"); /* end of the grid */
}

/**
 * @brief Asks the User for a CHAR input in order to choose where to play in the 'super grid'.
 * 
 * @param adrInput adress of the input variable.
 */
void inputWhichGrid(char *adrInput) // Done, need to add errors messages
{
    printf("In which grid do you wish to play (From 'A' to 'I'): ");
    
    bool condition = false;

    do
    {
        char input[3] = "";

        fgets(input, sizeof(input), stdin);
        fflush(stdin);

        /*-- Makes sure the input is not longer the 3 --*/

        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        else
        {
            // printf error too long
            while (getchar() != '\n');
            continue;
        }
        
        /*-- Main loop, checks if the user's input is correct --*/

        if (strlen(input) <= 1) /* If the input is only 1 character, */ 
        {        
            for (int row = 0; row < ROW; row++)
            {
                for (size_t col = 0; col < COLUMN; col++)
                {
                    if (input == letters[row][col]) /* checks if it's a correct letter, */
                    {
                        *adrInput = input;
                        condition = true;
                    }
                    else /* prints an error otherwise, asking the user to try again */
                    {
                        // printf error not in letters
                    }
                }
            }
        }
        else
        {
            // printf error too long
        }

        /* Clears the buffer before looping */
        while (getchar() != '\n');
    } while (!condition);
}

/**
 * @brief Asks the User for an INT input in order to choose where to play in the grid inside the 'super grid'.
 * 
 * @param adrInput Adress of the input variable.
 */
void inputWhichSquare(char *adrInput) // Done, need to add errors messages
{
    printf("In which square do you wish to play (From 1 to 3): ");
    
    bool condition = false;

    do
    {
        char input[3] = "";
        int value;

        fgets(input, sizeof(input), stdin);
        fflush(stdin);

        /*-- Makes sure the input is not longer than 3 --*/

        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        else
        {
            // printf error too long
            while (getchar() != '\n');
            continue;
        }
        
        /*-- Main loop, checks if the user's input is correct --*/

        if (sscanf(input, "%d", value) != false) /* Convert the STR to INT, prints error if it doesn't work */
        {
            if (value >= 1 && value <= 3) /* Checks if it's a correct number, */
            {
                value--;
                *adrInput = value; /* attributes it to the variable if correct, */
                condition = true;
            }
            else /* prints an error otherwise, asking the user to try again */
            {
                // printf error not in limits
            }
        }

        /* Clears the buffer before looping */
        while (getchar() != '\n');
    } while (!condition);
}

/**
 * @brief Checks if the given grid inside 'super grid' is complete.
 * 
 * @param superGrid Game's grid.
 * @param letter Letter of the grid to check, gives the index of said grid.
 * @return 1 if Player1 has finished it, 2 if Player2 did, 0 otherwise.
 */
int gridComplete(struct Grid superGrid[ROW][COLUMN], char letter) // Seems done
{
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COLUMN; col++) {

            if (letter == letters[row][col]) /* Finds the index of the current working grid inside of 'super grid' */
            {
                for (int gridRow = 0; gridRow < ROW; gridRow++) {

                    /*-- Checks the diagonals --*/

                    if (superGrid[row][col].grid[gridRow][gridRow] == 'X') { return P1; } /* Checks the diagonal from (0,0) to (2,2) for if P1 won */
                    if (superGrid[row][col].grid[gridRow][gridRow] == 'O') { return P2; } /* Checks the diagonal from (0,0) to (2,2) for if P2 won */

                    for (int gridDiag = 2; gridDiag >=0; gridDiag--) {
                        if (superGrid[row][col].grid[gridRow][gridDiag] == 'X') { return P1; } /* Checks the diagonal from (0,2) to (2,0) for if P1 won */
                        if (superGrid[row][col].grid[gridRow][gridDiag] == 'O') { return P2; } /* Checks the diagonal from (0,2) to (2,0) for if P2 won */
                    }

                    /*-- Checks the lines (Rows and Columns) --*/

                    for (int gridCol = 0; gridCol < COLUMN; gridCol++) {
                        if (superGrid[row][col].grid[gridRow][gridCol] == 'X') { return P1; } /* Checks each rows for if P1 won */
                        else if (superGrid[row][col].grid[gridCol][gridRow] == 'X') { return P1; } /* Checks each columns for if P1 won */

                        if (superGrid[row][col].grid[gridRow][gridCol] == 'O') { return P2; } /* Checks each rows for if P2 won */
                        else if (superGrid[row][col].grid[gridCol][gridRow] == 'O') { return P2; } /* Checks each columns for if P2 won */
                    }
                }
            }
        }
    }
    return 0;
}

/**
 * @brief Checks if the 'super grid' is completed, so if the game finished.
 * 
 * @param superGrid Game's grid.
 * @return 1 if Player1 has won, 2 if Player2 did, 0 otherwise.
 */
int superGridComplete(struct Grid superGrid[ROW][COLUMN]) // Seems done
{
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COLUMN; col++) {
            for (int invCol = 0; invCol < ROW; invCol--) {

                if (gridComplete(superGrid, letters[row][row]) == P1) { return P1; } /* Checks the diagonal from (0,0) to (2,2) for if P1 won */
                else if (gridComplete(superGrid, letters[row][row]) == P2) { return P2; } /* Checks the diagonal from (0,0) to (2,2) for if P2 won */

                else if (gridComplete(superGrid, letters[row][invCol]) == P1) { return P1; } /* Checks the diagonal from (0,2) to (2,0) for if P1 won */
                else if (gridComplete(superGrid, letters[row][invCol]) == P2) { return P2; } /* Checks the diagonal from (0,2) to (2,0) for if P2 won */

                else if (gridComplete(superGrid, letters[row][col]) == P1) { return P1; } /* Checks each rows for if P1 won */
                else if (gridComplete(superGrid, letters[col][row]) == P1) { return P1; } /* Checks each columns for if P1 won */

                else if (gridComplete(superGrid, letters[row][col]) == P2) { return P2; } /* Checks each rows for if P2 won */
                else if (gridComplete(superGrid, letters[col][row]) == P2) { return P2; } /* Checks each columns for if P2 won */
            }
        }
    }
    return 0;
}

/**
 * @brief Prints the initial welcome message.
 */
void welcome()
{
    printf(" ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                        By @powan5(dc)\n");
    printf("\n");
    printf("                                       Welcome!\n");
    printf("\n");
    printf("                                    [1]  Rules\n");
    printf("                                    [2]  Start a game (1P  (Coming at some point))\n");
    printf("                                    [3]  Start a match (2P)\n");
    printf("                                    [0]  Exit\n");
    printf("\n");
    printf("Please input your choice: ");
}
