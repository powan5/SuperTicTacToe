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

void PrintGrid(struct Grid superGrid[ROW][COLUMN]) // NEED TO RE DO (remove // when imput is done)
{
    // Prints the TOP outline of the 'super grid'
    for (int _ = 0; _ < ROW; _++)
    {
        printf("+-------------------");
    }
    printf("+\n");

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


        // Prints the BOTTOM outline of the 'super grid'
        for (int _ = 0; _ < ROW; _++)
        {
            printf("+-------------------");
        }
        printf("+\n");
    }
}

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

int gridComplete(struct Grid superGrid[ROW][COLUMN])
{
    for (int row = 0; row < ROW; row++)
    { // Row of super grid
        for (int col = 0; col < COLUMN; col++)
        { // Column of super grid
            for (int gridRow = 0; gridRow < ROW; gridRow++)
            { // Row of the grid inside superGrid[row][col]
                for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                { // Column of the grid inside superGrid[row][col]
                    superGrid[row][col].grid[gridRow][gridCol] == 'X';
                }
            }
        }
    }
}
}