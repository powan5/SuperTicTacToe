#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// Const // USE SIZE (1d) && ROW & COLUMN (2d)
#define ROW 3
#define COLUMN 3
#define P1 1
#define P2 2
typedef struct Grid
{
    char grid[ROW][COLUMN];
};
 
typedef char List[ROW][COLUMN];

const List letters = {{'A','B','C'}, {'D','E','F'}, {'G','H','I'}};

// Prototypes init
void PrintGrid(struct Grid superGrid[ROW][COLUMN]);
void initSuperGrid(struct Grid superGrid[ROW][COLUMN]);
void inputWhichGrid(char *adrInput);

int main()
{
    // Variables
    struct Grid grid;
    struct Grid superGrid[ROW][COLUMN];


    // Inputs
    // while (getchar() != '\n');  // Buffer clear (if usage of strings)
    initSuperGrid(superGrid);


    // Printing of the grid
    printf("\033[2J\033[1;1H"); // Clears output terminal
    PrintGrid(superGrid);


    return EXIT_SUCCESS;
}

// definition of Prototypes

/**
 * @brief Initialise 'the super grid's grids values with 'Z'.
 * 
 * @param superGrid Game's grid.
 */
void initSuperGrid(struct Grid superGrid[ROW][COLUMN]) //Finished
{ // Sets every square of the grids inside the 'super grid' to 'Z' (for Zero)
    for (int row = 0; row < ROW; row++)
    { // Row of super grid
        for (int col = 0; col < COLUMN; col++)
        { // Column of super grid
            for (int gridRow = 0; gridRow < ROW; gridRow++)
            { // Row of the grid inside superGrid[row][col]
                for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                { // Column of the grid inside superGrid[row][col]
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
void PrintGrid(struct Grid superGrid[ROW][COLUMN]) // NEED TO RE-DO (remove // when input is done)
{
    // Prints the TOP outline of the 'super grid'
    for (int _ = 0; _ < ROW; _++)
    {
        printf("+-------------------");
    }
    printf("+\n");


    /**
     * NEED TO RE-DO THIS PART aka basically everything
     * Why? Cuz I need to print X or O when the tinyGrid is done by either
    */

    // Prints the middle of 'super grid'
    for (int row = 0; row < ROW; row++)
    { // Divided in rows of 3
        
        int num = 1; // For the grids indexs (UI element only)
        
        
        // Devides each rows in a row with columns, and prints the TOP row of letters (for the supder grid index) and numbers (for the grid index)
        for (int col = 0; col < COLUMN; col++)
        { 
            printf("| %c   ", letters[row][col]);
            for (int num = 1; num <= ROW; num++)
            {
                printf("%d   ", num);
            }
            printf("%c ", letters[row][col]);
        }
        printf("|\n");

        
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
                printf("| %d ", num); // Index number
                
                for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                {
                    printf("| ");
                    // Prints '.' if no value, 'X' or 'O' otherwise
                    if (superGrid[row][col].grid[gridRow][gridCol] == 'Z')
                    {
                        printf(". ");
                    }
                    //else
                    //{
                    //    printf("%s ", superGrid[row][num].grid[gridRow][gridCol]);
                    //}
                }
                printf("| %d ", num);
            }
            
            printf("|\n");
            num++;
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
            printf("| %c   ", letters[row][col]);
            for (int num = 1; num <= ROW; num++)
            {
                printf("%d   ", num);
            }
            printf("%c ", letters[row][col]);
        }
        printf("|\n");



        // Prints the BOTTOM & MIDDLE outline of the 'super grid'
        for (int _ = 0; _ < ROW; _++)
        {
            printf("+-------------------");
        }
        printf("+\n");
    }
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

        fgets(input, sizeof(input), stdin); // Gets input
        fflush(stdin); // Clears the input terminal

        // Makes sure the input is not longer the 3
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
        
        // If the input is only 1 character,  
        if (strlen(input) <= 1)
        {        
            for (int row = 0; row < ROW; row++)
            {
                for (size_t col = 0; col < COLUMN; col++)
                {
                    if (input == letters[row][col]) // checks if it's a correct letter,
                    {
                        *adrInput = input;
                        condition = true;
                    }
                    else // prints an error otherwise, and ask the user to try again
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

        // Clears the input terminal before looping
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

        fgets(input, sizeof(input), stdin); // Gets input
        fflush(stdin); // Clears the input terminal

        // Makes sure the input is not longer the 3
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
        

        if (sscanf(input, "%d", value) != false)
        {
            if (value >= 1 && value <= 3) // checks if it's a correct number,
            {
                value--;
                *adrInput = value;
                condition = true;
            }
            else // prints an error otherwise, and ask the user to try again
            {
                // printf error not in limits
            }
        }

        // Clears the input terminal before looping
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
    for (int row = 0; row < ROW; row++)
    { // Row of super grid
        for (int col = 0; col < COLUMN; col++)
        { // Column of super grid

            if (letter == letters[row][col])
            {
                for (int gridRow = 0; gridRow < ROW; gridRow++)
                { // Row of the grid inside superGrid[row][col]

                    if (superGrid[row][col].grid[gridRow][gridRow] == 'X') { return P1; } // Checks the diagonal from (0,0) to (2,2) for P1 win
                    if (superGrid[row][col].grid[gridRow][gridRow] == 'O') { return P2; } // Checks the diagonal from (0,0) to (2,2) for P2 win

                    for (int gridDiag = 2; gridDiag >=0; gridDiag--)
                    {
                        if (superGrid[row][col].grid[gridRow][gridDiag] == 'X') { return P1; } // Checks the diagonal from (0,2) to (2,0) for P1 win
                        if (superGrid[row][col].grid[gridRow][gridDiag] == 'O') { return P2; } // Checks the diagonal from (0,2) to (2,0) for P2 win
                    }

                    for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                    { // Column of the grid inside superGrid[row][col]
                        if (superGrid[row][col].grid[gridRow][gridCol] == 'X') { return P1; } // Checks each rows for P1 wins
                        else if (superGrid[row][col].grid[gridCol][gridRow] == 'X') { return P1; } // Checks each columns for P1 wins

                        if (superGrid[row][col].grid[gridRow][gridCol] == 'O') { return P2; } // Checks each rows for P2 wins
                        else if (superGrid[row][col].grid[gridCol][gridRow] == 'O') { return P2; } // Checks each columns for P2 wins
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
    for (int row = 0; row < ROW; row++)
    { // Row of super grid
        for (int col = 0; col < COLUMN; col++)
        { // Column of super grid
            for (int invCol = 0; invCol < ROW; invCol--)
            { // Row of the grid inside superGrid[row][col]

                if (gridComplete(superGrid, letters[row][row]) == P1) { return P1; } // Checks the diagonal from (0,0) to (2,2) for P1 win
                else if (gridComplete(superGrid, letters[row][row]) == P2) { return P2; } // Checks the diagonal from (0,0) to (2,2) for P2 win

                else if (gridComplete(superGrid, letters[row][invCol]) == P1) { return P1; } // Checks the diagonal from (0,2) to (2,0) for P1 win
                else if (gridComplete(superGrid, letters[row][invCol]) == P2) { return P2; } // Checks the diagonal from (0,2) to (2,0) for P2 win

                else if (gridComplete(superGrid, letters[row][col]) == P1) { return P1; } // Checks each rows for P1 wins
                else if (gridComplete(superGrid, letters[col][row]) == P1) { return P1; } // Checks each columns for P1 wins

                else if (gridComplete(superGrid, letters[row][col]) == P2) { return P2; } // Checks each rows for P2 wins
                else if (gridComplete(superGrid, letters[col][row]) == P2) { return P2; } // Checks each columns for P2 wins
            }
        }
    }
    return 0;
}

