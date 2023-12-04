#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// Const // USE SIZE (1d) && ROW & COLUMN (2d)
#define ROW 3
#define COLUMN 3
typedef struct Grid
{
    char grid[ROW][COLUMN];
};
 
typedef char List[ROW][COLUMN];
 

// Prototypes init
void PrintGrid(struct Grid superGrid[ROW][COLUMN]);
void initSuperGrid(struct Grid superGrid[ROW][COLUMN]);


int main()
{
    // Variables
    struct Grid grid;
    struct Grid superGrid[ROW][COLUMN];


    // Inputs
    // while (getchar() != '\n');  // Buffer clear (if usage of strings)
    initSuperGrid(superGrid);


    // Printing of the grid
    PrintGrid(superGrid);


    return EXIT_SUCCESS;
}

// definition of Prototypes

void initSuperGrid(struct Grid superGrid[ROW][COLUMN]) //Finished
{
    for (int row = 0; row < ROW; row++){
        for (int col = 0; col < COLUMN; col++){
            for (int gridRow = 0; gridRow < ROW; gridRow++){
                for (int gridCol = 0; gridCol < COLUMN; gridCol++){
                    superGrid[row][col].grid[gridRow][gridCol] = 'Z';
                }
            }
        }
    }
}

void PrintGrid(struct Grid superGrid[ROW][COLUMN]) // Finished (remove // when imput is done)
{
    List letters = {{'A','B','C'}, {'D','E','F'}, {'G','H','I'}};
    

    for (int _ = 0; _ < ROW; _++)
    {
        printf("+-------------------");
    }
    printf("+\n");

    for (int row = 0; row < ROW; row++)
    {
        int num = 1;
        
        
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

        
        for (int col = 0; col < COLUMN; col++)
        {
            for (int _ = 0; _ < ROW; _++)
            {
                printf("|   +---+---+---+   ");
            }
            printf("|\n");
            
            for (int gridRow = 0; gridRow < ROW; gridRow++)
            {
                printf("| %d ", num);
                
                for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                {
                    printf("| ");
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
        for (int _ = 0; _ < ROW; _++)
        {
            printf("|   +---+---+---+   ");
        }
        printf("|\n");
    
    
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
        for (int _ = 0; _ < ROW; _++)
        {
            printf("+-------------------");
        }
        printf("+\n");
    }
}
