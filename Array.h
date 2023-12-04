#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int List[SIZE];
typedef int Grid[ROW][COLUMN];

// Function to initialise a 1d array with a given value

extern void intitialiseArray1d(List array, int sizeOfArray, int defaultValue)
{
    for (int index = 0; index < sizeOfArray; index++) array[index] = defaultValue;
}

// Function to initialise a 2d array with a given value

extern void intitialiseArray2d(Grid array, int row, int column, int defaultValue)
{
    for (int indexRow = 0; indexRow < row; indexRow++)
    {
        for (int indexColumn = 0; indexColumn < column; indexColumn++) array[indexRow][indexColumn] = defaultValue;
    }
}

// Function to find a value in an array of 1 dimension

extern bool FindValueArray1d(List array, int size, int value)
{
    bool result = false;
    for (int index = 0; index < size && !result; index++) result = (array[index] == value);
    return result;
}

// Function to find a value in an array of 2 dimensions

extern bool FindValueArray2d(Grid array, int row, int column, int value)
{
    bool result = false;
    for (int indexRow = 0; indexRow < row && !result; indexRow++)
    {
        for (int indexColumn = 0; indexColumn < column && !result; indexColumn++) result = (array[indexRow][indexColumn] == value);
    }
    return result;
}

// Function to print a 1d array in a terminal

extern void printArray1d(List array, int size)
{
    for (int index = 0; index < size; index++) printf("%3d", array[index]);
}

// Function to print a 2d array in a terminal

extern void printArray2d(Grid array, int row, int column)
{
    for (int indexRow = 0; indexRow < row; indexRow++)
    {
        for (int indexColumn = 0; indexColumn < column; indexColumn++) printf("%3d", array[indexRow][indexColumn]);
        printf("\n");
    }
}