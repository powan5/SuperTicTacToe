#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "Array.h"

// Const // USE SIZE (1d) && ROW & COLUMN (2d)
#define ROW 3
#define COLUMN 3
typedef char Grid[ROW][COLUMN];
typedef char List[ROW][COLUMN];

typedef Grid SuperGrid[ROW][COLUMN];

// Prototypes
void PrintGrid(Grid grid);

int main()
{
    // Variables
    Grid grid;
    SuperGrid superGrid;


    // Inputs
    // while (getchar() != '\n');  // Buffer clear (if usage of strings)


    // Printing of the grid
    initSuperGrid(superGrid);   
    printArray2d(superGrid, ROW, COLUMN);



    return EXIT_SUCCESS;
}

// definition des prototypes

void initGrid(Grid grid)
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {
            grid[row][col] = 'Z';
        }
    }
}

void initSuperGrid(SuperGrid superGrid)
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {
            Grid grid;
            initGrid(grid);
            superGrid[row][col] = grid;
        }
    }
}

void PrintGrid(Grid grid)
{
    List letters = {{'A','B','C'}, {'D','E','F'}, {'G','H','I'}};


    for (int _ = 0; _ < ROW; _++)
    {
        printf("+-------------------");
    }
    printf("+\n");

    for (int row = 0; row < ROW; row++)
    {
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

        
        
        for (int num = 1; num <= ROW; num++)
        {
            for (int _ = 0; _ < ROW; _++)
            {
                printf("|   +---+---+---+   ");
            }
            printf("|\n");
            for (int _ = 0; _ < ROW; _++)
            {
                printf("| %d ", num);
                printf("| . | . | . ");
                printf("| %d ", num);
            }
            printf("|\n");
            
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
