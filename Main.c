/**
 * @brief Program to play Super Tic-Tac-Toe, a variation of tic-tac-toe where players need to complete a grid in order to claim a square of the main grid ('super grid')
 * 
 * @author Powan
 * @version Beta 1.0.2
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

typedef char * BigXandO[1][COLUMN];
const BigXandO X = {{'|                   '},{'|                   '},{'|       \\   /       '}, {'|       \\ /         '}, {'|         X         '}, {'|        / \\        '}, {'|       /   \\       '},{'|                   '},{'|                   '}};
const BigXandO O = {{'|                   '},{'|                   '},{'|    /---------\\    '}, {'|    |         |    '}, {'|    |         |    '}, {'|    |         |    '}, {'|    \\---------/    '},{'|                   '},{'|                   '}};

/*-- Prototypes initialisation --*/

/**
 * @brief Initialise 'the super grid's grids values with 'Z'.
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


    /*-- Inputs --*/

    initSuperGrid(superGrid);


    /*-- Printing of the grid --*/

    printf("\033[2J\033[1;1H"); // Clears output terminal
    PrintGrid(superGrid);


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
                    superGrid[row][col].grid[gridRow][gridCol] = 'Z';
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
void PrintGrid(struct Grid superGrid[ROW][COLUMN]) // NEED TO RE-DO
{
    for (int superRow = 0; superRow < ROW; superRow++)
    {
        int indexTinyRow = 1;
        printf("+-------------------+-------------------+-------------------+\n");
        for (int superCol = 0; superCol < COLUMN; superCol++)
        {
            int tinyRowIndex = 0;
            if (gridComplete(superGrid, letters[superRow][superCol]) == 1)
            {
                for (int tinyRow = 0; tinyRow < ROW; tinyRow++)
                {
                    /*-- Checks if P1 won a square in 'super grid' --*/
                    if (superCol == 0)
                    {
                        /* Prints the big X */
                        printf("%s", X[0][tinyRow]);

                        /* Prints the rest */

                        /* The TOP & BOTTOM part, with indexs*/
                        if (tinyRow == 0 || tinyRow == 8)
                        {
                            for (int tinyCol = 0; tinyCol < COLUMN; tinyCol++)
                            {
                                { 
                                    printf("| %c   ", letters[superRow][superCol]);
                                    for (int indexTinyCol = 1; indexTinyCol <= ROW; indexTinyCol++)
                                    {
                                        printf("%d   ", indexTinyCol);
                                    }
                                    printf("%c ", letters[superRow][superCol]);
                                }
                            }
                        }
                        
                        for (int _ = 0; _ < ROW; _++) // Separation lines
                        {
                            printf("|   +---+---+---+   ");
                        }
                        printf("|\n");
                        
                        for (int gridRow = 0; gridRow < ROW; gridRow++)
                        {
                            printf("| %d ", indexTinyRow);
                            
                            for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                            {
                                printf("| ");
                                // Prints '.' if no value, 'X' or 'O' otherwise
                                if (superGrid[superRow][superCol].grid[gridRow][gridCol] == 'Z')
                                {
                                    printf(". ");
                                }
                                //else
                                //{
                                //    printf("%s ", superGrid[row][indexTinyRow].grid[gridRow][gridCol]);
                                //}
                            }
                            printf("| %d ", indexTinyRow);
                        }
                        
                        printf("|\n");
                        indexTinyRow++;
                        
                    }
                    else if (superCol == 1)
                    {
                        printf("%s", X[0][tinyRow]);
                    }
                    else if (superCol == 2)
                    {
                        printf("%s", X[0][tinyRow]);
                    }
                    else
                    {
                        // Divides each rows in a row with columns, and prints the grids insides of the 'super grid', with indexs of the side
                        for (int col = 0; col < COLUMN; col++)
                        {
                            for (int _ = 0; _ < ROW; _++) // Separation lines
                            {
                                printf("|   +---+---+---+   ");
                            }
                            printf("|\n");

                            for (int gridRow = 0; gridRow < ROW; gridRow++)
                            {
                                printf("| %d ", indexTinyRow); // Index number

                                for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                                {
                                    printf("| ");
                                    // Prints '.' if no value, 'X' or 'O' otherwise
                                    if (superGrid[superRow][superCol].grid[gridRow][gridCol] == 'Z')
                                    {
                                        printf(". ");
                                    }
                                    //else
                                    //{
                                    //    printf("%s ", superGrid[row][num].grid[gridRow][gridCol]);
                                    //}
                                }
                                printf("| %d ", indexTinyRow);
                            }

                            printf("|\n");
                            indexTinyRow++;
                        }
                        // Prints the last separation line
                        for (int _ = 0; _ < ROW; _++)
                        {
                            printf("|   +---+---+---+   ");
                        }
                        printf("|\n");


                        // Devides each rows in a row with columns, and prints the BOTTOM row of letters (for the supder grid index) and numbers (for the grid index)
                        for (int col = 0; col < COLUMN; col++)
                        { 
                            printf("| %c   ", letters[superRow][superCol]);
                            for (int num = 1; num <= ROW; num++)
                            {
                                printf("%d   ", num);
                            }
                            printf("%c ", letters[superRow][superCol]);
                        }
                        printf("|\n");
                    }
                    

                    for (int tinyCol = 0; tinyCol < COLUMN; tinyCol++)
                    {
                        
                    }
                }
            }
            for (int tinyRow = 0; tinyRow < ROW; tinyRow++)
            {
                
                
                for (int tinyCol = 0; tinyCol < COLUMN; tinyCol++)
                {

                }
            }
        }
    }
    printf("+-------------------+-------------------+-------------------+\n");
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



/* AAAAAAAAAAAAHH sector */


//     // Prints the middle of 'super grid'
//     for (int row = 0; row < ROW; row++)
//     { // Divids in rows of 3
//         
//         int num = 1; // For the grids indexs (UI element only)
//         
//         
//         // Devides each rows in a row with columns, and prints the TOP row of letters (for the supder grid index) and numbers (for the grid index)
//         for (int col = 0; col < COLUMN; col++)
//         { 
//             printf("| %c   ", letters[row][col]);
//             for (int num = 1; num <= ROW; num++)
//             {
//                 printf("%d   ", num);
//             }
//             printf("%c ", letters[row][col]);
//         }
//         printf("|\n");
// 
//         /**
//          * NEED TO RE-DO THIS PART (basically everything)
//          * Why? Cuz I need to print X or O when the tinyGrid is done by either
//      */
//         // Divides each rows in a row with columns, and prints the grids insides of the 'super grid', with indexs of the side
//         for (int col = 0; col < COLUMN; col++)
//         {
//             for (int _ = 0; _ < ROW; _++) // Separation lines
//             {
//                 printf("|   +---+---+---+   ");
//             }
//             printf("|\n");
//             
//             for (int gridRow = 0; gridRow < ROW; gridRow++)
//             {
//                 printf("| %d ", num); // Index number
//                 
//                 for (int gridCol = 0; gridCol < COLUMN; gridCol++)
//                 {
//                     printf("| ");
//                     // Prints '.' if no value, 'X' or 'O' otherwise
//                     if (superGrid[row][col].grid[gridRow][gridCol] == 'Z')
//                     {
//                         printf(". ");
//                     }
//                     //else
//                     //{
//                     //    printf("%s ", superGrid[row][num].grid[gridRow][gridCol]);
//                     //}
//                 }
//                 printf("| %d ", num);
//             }
//             
//             printf("|\n");
//             num++;
//         }
//         // Prints the last separation line
//         for (int _ = 0; _ < ROW; _++)
//         {
//             printf("|   +---+---+---+   ");
//         }
//         printf("|\n");
// 
// 
//         // Devides each rows in a row with columns, and prints the BOTTOM row of letters (for the supder grid index) and numbers (for the grid index)
//         for (int col = 0; col < COLUMN; col++)
//         { 
//             printf("| %c   ", letters[row][col]);
//             for (int num = 1; num <= ROW; num++)
//             {
//                 printf("%d   ", num);
//             }
//             printf("%c ", letters[row][col]);
//         }
//         printf("|\n");
// 
// 
// 
//         // Prints the BOTTOM & MIDDLE outline of the 'super grid'
//         for (int _ = 0; _ < ROW; _++)
//         {
//             printf("+-------------------");
//         }
//         printf("+\n");
//     }