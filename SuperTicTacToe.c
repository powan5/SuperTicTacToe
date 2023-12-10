/**
 * @brief Program to play Super Tic-Tac-Toe, a variation of tic-tac-toe where players need to complete a grid in order to claim a square of the main grid ('super grid')
 * 
 * @author Powan
 * @version Alpha 1.0.2
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
/* printf("\033[2J\033[1;1H"); // Clears output terminal */

/****************************************************/
/*******|         Constants & Types          |*******/
/****************************************************/

#define CLEAR_TERMINAL "\033[2J\033[1;1H"

#define ROW 3
#define COLUMN 3
#define P1 1
#define P2 2

typedef struct Grid { char grid[ROW][COLUMN]; };

typedef char List[ROW][COLUMN];
const List LETTERS = {{'A','B','C'}, {'D','E','F'}, {'G','H','I'}};

typedef char * gridBlocks[3][9];    

/* Error codes (there is a logic to it, try to fint it I'll give you a cookie :D) */

#define DEBUG 686671

#define INPUT_TOO_LONG 105116108
#define NON_INT_INPUT 110105105
#define INT_OUT_OF_RANGE 105111114
#define NON_CHAR_INPUT 11099105
#define CHAR_INPUT_UNRECONIZED 99105117
#define CELL_TAKEN 99116107
#define PLAYER_ID 112105100


/****************************************************/
/***|         Prototypes Initialisation          |***/
/****************************************************/


/* Miscellaneous */

/**
 * @brief Prints the error messages.
 * 
 * @param code Error code, int.
*/
void errors(int code);
/**
 * @brief Prints a little loading animation.
*/
void loading();
/**
 * @brief Prints the initial welcome message.
*/
void welcome();
/**
 * @brief Prints the rules of the Super Tic-Tac-Toe.
*/
void rules();
/**
 * @brief Asks the User for a CHAR input, for his pseudo.
 * 
 * @param adrInput Adress of the input variable.
*/
void namePlayer(char *adrInput);


/* Super Grid & Grids related stuff */

/**
 * @brief Initialise "the super grid's grids values with 'Z'.
 * 
 * @param superGrid Game's grid.
*/
void initSuperGrid(struct Grid superGrid[ROW][COLUMN]);
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


/* Inputs */

/**
 * @brief Asks the User for a CHAR input in order to choose where to play in the 'super grid'.
 * 
 * @param adrInput adress of the input variable (CHAR).
*/
void inputWhichGrid(char *adrInput);
/**
 * @brief Asks the User for an INT input in order to choose where to play in the grid inside the 'super grid'.
 * 
 * @param adrInput Adress of the input variable (INT).
*/
void inputWhichCell(int *adrInput);
/**
 * @brief Have a player takes his turn and play.
 * 
 * @param superGrid Game's grid.
 * @param player The players id, to know if it's 'X'or'O's turn.
 * @param letter Letter used to know the grifd in where the player plays.
*/
void play(struct Grid superGrid[ROW][COLUMN], int player, char letter);



/****************************************************/
/**************|         MAIN         |**************/
/****************************************************/

int main()
{
    /*-- Variables --*/

    struct Grid grid;
    struct Grid superGrid[ROW][COLUMN]; 
    initSuperGrid(superGrid);
    printf("%c\n", superGrid[1][1].grid[1][1]);
    int choice = -1;

    welcome();

    /*-- Main loop --*/

    do
    {
        printf("Please input your choice: ");
        scanf("%d", &choice);
        
        /*-- Exit --*/
        if (choice == 0)
        {
            printf("Exiting");
            loading();
            return EXIT_SUCCESS;
        } else
        
        /****************************************************/
        /**************|         Rules        |**************/
        /****************************************************/

        if (choice == 1)
        {
            char PressEnterToContinue = 0;
            rules();
            while (PressEnterToContinue != '\r' && PressEnterToContinue != '\n') { PressEnterToContinue = getchar(); }
            choice = -1;
            welcome();
        } else

        /****************************************************/
        /*************|     1 Player match     |*************/
        /****************************************************/

        if (choice == 2)
        {
            welcome();
            printf("This option is yet to be available. 2 players matches is the only option for now.\n");
            choice = -1;
        } else

        /****************************************************/
        /**************|    2 Player match    |**************/
        /****************************************************/

        if (choice == 3)
        {
            char rematch;
            //printf("%s", CLEAR_TERMINAL);
            printf("Initialising");
            loading();

            do
            {
                //printf("%s", CLEAR_TERMINAL);

                /* Get the pseudo for both players */
                char nameP1[20] = "";
                char nameP2[20] = "";
                while (getchar() != '\n'); /* Clears entry buffer */
                printf("Player 1 please choose you pseudo ('*' for a random one): ");
                namePlayer(nameP1);
                printf("Player 2 please choose you pseudo ('*' for a random one): ");
                namePlayer(nameP2);

                printf("%s will play 'X' & ", nameP1);
                printf("%s will play 'O'", nameP2);
                
                int player = 1;
                int turn = 0;
                char letter = 'Z';
                int row, column;

                sleep(1);

                do
                {
                    turn++; /* REMEMBER TO GIVE THE NB OF TURNS AT THE END */

                    PrintGrid(superGrid);

                    /* Checks which player's turn it is */
                    if (player == P1) { printf("%s to play, ", nameP1); }
                    else if (player == P2) { printf("%s to play, ", nameP2); }
                    else { player = P1; }
                    

                    /* If the game has just started or the supposed cell to play in is completed */
                    if (letter == 'Z' || gridComplete(superGrid, letter)) { inputWhichGrid(&letter); }
                    
                    /* Reminds which cell the player is in */
                    printf("\nYou are playing in the '%c' cell.\n\n", letter);

                    play(superGrid, player, letter);

                    errors(DEBUG); //temp

                    player++;
                } while (true /*superGridComplete(superGrid) == 0*/); //temp
                errors(DEBUG);
                
            printf("Wanna rematch ? [Y]/[N] ");
            scanf("%c", &rematch);
            rematch = toupper(rematch);
            } while (rematch != 'Y');
        }
    } while (choice == -1);

    return EXIT_SUCCESS;
}



/****************************************************/
/*****|         Prototypes definitions         |*****/
/****************************************************/


/* Miscellaneous */

/**
 * @brief Prints the error messages.
 * 
 * @param code Error code, int.
*/
void errors(int code)
{
    switch (code)
    {
    case DEBUG:
        printf("Successfully reached checkpoint.\n");
        break;

    case INPUT_TOO_LONG:
        printf("Error! The input is too long.\nTry again: ");
        break;

    case NON_INT_INPUT:
        printf("Error! Please input an integer.\nTry again: ");
        break;

    case INT_OUT_OF_RANGE:
        printf("Error! Please input an integer between 1 & 3.\nTry again: ");
        break;

    case NON_CHAR_INPUT:
        printf("Error! Please input a character.\nTry again: ");
        break;
        
    case CHAR_INPUT_UNRECONIZED:
        printf("Error! Please input a character included between A & I.\nTry again: ");
        break;

    case CELL_TAKEN:
        printf("Error! That cell has already been claimed.\nTry again: ");
        break;

    case PLAYER_ID: /* If this error is reached, the program can't continue without errors, so exits it before crashing. */
        printf("There was an error with the players' IDs... Exiting"); loading();
        exit(EXIT_FAILURE);
        break;

    default: /* This error is not supposed to happen, so exits the program before it crashs by itself. */
        printf("Error within the errors() function... Exiting"); loading();
        exit(EXIT_FAILURE);
        break;
    }
}

/**
 * @brief Prints a little loading animation.
*/
void loading()
{
    /* Cuz it looks cool 😎 */
    for (int _ = 0; _ < 3; _++)
    {
        fflush(stdout);
        sleep(1);
        printf(".");
    }
    printf("\n");
}

/**
 * @brief Prints the initial welcome message.
*/
void welcome()
{
    //printf("%s", CLEAR_TERMINAL);
    printf(" ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                        By @powan5(dc)\n");
    printf("\n");
    printf("\t\tWELCOME!\n");
    printf("\n");
    printf("\t[1]  Rules\n");
    printf("\t[2]  Start a game (1P (Coming at some point))\n");
    printf("\t[3]  Start a match (2P)\n");
    printf("\t[0]  Exit\n");
    printf("\n");
}

/**
 * @brief Prints the rules of the Super Tic-Tac-Toe.
*/
void rules()
{
    //printf("%s", CLEAR_TERMINAL);
    printf(" ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                        By @powan5(dc)\n");
    printf("\n");
    printf("                                                                                      \n");
    printf("                                        RULES                                        \n");
    printf("\n");
    printf("The game starts with a move in any of the nine 3x3 grids, choosen by Player 1. (From A to I)\n");
    printf("\n");
    printf("The opponent must play in the corresponding cell of the larger grid, \n");
    printf("based off of in which cell of the small grid the previous player played in.\n");
    printf("\n");
    printf("Winning a small grid awards that grid to the player and determines the opponent's next move.\n");
    printf("\n");
    printf("To win the game, you have to win three small grids in a row horizontally, vertically, or diagonally.\n");
    printf("\n");
    printf("If a player is meant to play in an already won small grid, they can choose any open cell.\n");
    printf("\n");
    printf("The game continues until a player wins the larger grid.\n");
    printf("\n");
    printf("If one of the small grid is full (a draw), said grid will be reseted for players to continue playing.\n");
    printf("\n");
    printf("[Press ENTER to continue]\n");
    while (getchar() != '\n');
}

/**
 * @brief Asks the User for a CHAR input, for his pseudo.
 * 
 * @param adrInput Adress of the input variable.
*/
void namePlayer(char *adrInput)
{
    bool condition = false;

    do
    {
        char input[20] = "";

        fgets(input, sizeof(input), stdin);
        fflush(stdin);

        /*-- Makes sures the input is not longer than 20 --*/

        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        else
        {
            errors(INPUT_TOO_LONG);
            while (getchar() != '\n');
            continue;
        }

        /*-- Gives the input as pseudo for the player --*/
        
        
        if (input[0] == '*') /* Gets a random pseudo to the player if he so desires */
        {
            // temp
            printf("This functionality is yet to be implemented, please choose a pseudo (excluding '*').\n");
            namePlayer(adrInput); // Calls the function again until input != '*' cuz this isn't done
        }
        else /* Gives the choosen pseudo otherwise */
        {
            strcpy(adrInput, input);
            condition = true;
        }
    } while (!condition);
}


/* Super Grid & Grids related stuff */

/**
 * @brief Initialise 'the super grid's grids values with 'Z'.
 * 
 * @param superGrid Game's grid.
*/
void initSuperGrid(struct Grid superGrid[ROW][COLUMN])
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
 * @brief Checks if the given grid inside 'super grid' is complete.
 * 
 * @param superGrid Game's grid.
 * @param letter Letter of the grid to check, gives the index of said grid.
 * @return 1 if Player1 has finished it, 2 if Player2 did, 0 otherwise.
*/
int gridComplete(struct Grid superGrid[ROW][COLUMN], char letter)
{
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COLUMN; col++) {

            if (letter == LETTERS[row][col]) /* Finds the index of the current working grid inside of 'super grid' */
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
int superGridComplete(struct Grid superGrid[ROW][COLUMN])
{
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COLUMN; col++) {
            for (int invCol = 0; invCol < ROW; invCol--) {

                /*-- Checks the diagonals --*/

                if (gridComplete(superGrid, LETTERS[row][row]) == P1) { return P1; } /* Checks the diagonal from (0,0) to (2,2) for if P1 won */
                else if (gridComplete(superGrid, LETTERS[row][row]) == P2) { return P2; } /* Checks the diagonal from (0,0) to (2,2) for if P2 won */

                else if (gridComplete(superGrid, LETTERS[row][invCol]) == P1) { return P1; } /* Checks the diagonal from (0,2) to (2,0) for if P1 won */
                else if (gridComplete(superGrid, LETTERS[row][invCol]) == P2) { return P2; } /* Checks the diagonal from (0,2) to (2,0) for if P2 won */

                /*-- Checks the lines (Rows and Columns) --*/

                else if (gridComplete(superGrid, LETTERS[row][col]) == P1) { return P1; } /* Checks each rows for if P1 won */
                else if (gridComplete(superGrid, LETTERS[col][row]) == P1) { return P1; } /* Checks each columns for if P1 won */

                else if (gridComplete(superGrid, LETTERS[row][col]) == P2) { return P2; } /* Checks each rows for if P2 won */
                else if (gridComplete(superGrid, LETTERS[col][row]) == P2) { return P2; } /* Checks each columns for if P2 won */
            }
        }
    }
    return 0;
}

/**
 * @brief Prints the game's grid in the terminal.
 * 
 * @param superGrid Game's grid.
*/
void PrintGrid(struct Grid superGrid[ROW][COLUMN])
{
    //printf("%s", CLEAR_TERMINAL);

    /*-- Output template --*/

    gridBlocks LETTERS = {
        { /* Main grid */
        "| %c   1   2   3   %c ",
        "|   +---+---+---+   ",
        "| 1 | %c | %c | %c | 1 ",
        "|   +---+---+---+   ",
        "| 2 | %c | %c | %c | 2 ",
        "|   +---+---+---+   ",
        "| 3 | %c | %c | %c | 3 ",
        "|   +---+---+---+   ",
        "| %c   1   2   3   %c "},
        { /* Grid completed by P1 */
        "|                   ",
        "|                   ",
        "|       \\   /       ",
        "|        \\ /        ",
        "|         X         ",
        "|        / \\        ",
        "|       /   \\       ",
        "|                   ",
        "|                   "},
        { /* Grid completed by P2 */
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

                    switch (gridComplete(superGrid, LETTERS[superRow][superCol])) /* Checks if a player has won a square of the 'super grid' or not */
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
                        if (tinyRowIndex == 0 || tinyRowIndex == 8) /* "| %c   1   2   3   %c |" */
                        {
                           sprintf(printableLine, LETTERS[0][tinyRowIndex], LETTERS[superRow][tinyCol], LETTERS[superRow][tinyCol]);
                           printf("%s", printableLine);
                           char printableLine[20] = "";
                           break; 
                        }
                        else if (tinyRowIndex == 1 || tinyRowIndex == 3 || tinyRowIndex == 5 || tinyRowIndex == 7) /* "|   +---+---+---+   |" */
                        {
                           printf("%s", LETTERS[0][tinyRowIndex]); 
                           break; 
                        }
                        else /* "| [nb] | %c | %c | %c | [nb] |" */
                        {
                           sprintf(printableLine, LETTERS[0][tinyRowIndex], superGrid[superRow][superCol].grid[tinyRow][tinyRowIndex%3], superGrid[superRow][superCol].grid[tinyRow][tinyRowIndex%3], superGrid[superRow][superCol].grid[tinyRow][tinyRowIndex%3]);
                           printf("%s", printableLine); 
                           char printableLine[20] = "";
                           break; 
                        }
                        break;
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


/* Inputs */

/**
 * @brief Asks the User for a CHAR input in order to choose where to play in the 'super grid'.
 * 
 * @param adrInput adress of the input variable.
*/
void inputWhichGrid(char *adrLetter)
{
    printf("In which grid do you wish to play (From 'A' to 'I'): ");
    
    bool condition = false;

    do
    {
        char input[2];

        fgets(input, sizeof(input), stdin);
        fflush(stdin);
        
        /*-- Main loop, checks if the user's input is correct --*/
        
        int temp;
        if (sscanf(input, "%d", &temp) != false) /* Checks if the user inputed an int */
        { 
            errors(NON_CHAR_INPUT);
        }

        /* Checks if it's a correct letter */
        for (int row = 0; row < ROW; row++)
        {
            for (size_t col = 0; col < COLUMN; col++)
            {
                char upperInput = toupper(input[0]);
                if (upperInput == LETTERS[row][col]) /* if it is, outputs it, */
                {
                    *adrLetter = upperInput;
                    condition = true;
                }
            }
        }
        if (!condition) { errors(CHAR_INPUT_UNRECONIZED); } /* prints an error otherwise, asking the user to try again */

        /* Clears the buffer before looping */
        while (getchar() != '\n');
    } while (!condition);
}

/**
 * @brief Asks the User for an INT input in order to choose where to play in the grid inside the 'super grid'.
 * 
 * @param adrInput Adress of the input variable.
*/
void inputWhichCell(int *adrInput)
{
    printf("In which square do you wish to play (From 1 to 3): ");
    
    bool condition = false;

    do
    {
        char input[3] = "";
        int value;

        fgets(input, sizeof(input), stdin);
        fflush(stdin);

        /*-- Makes sures the input is not longer than 3 --*/

        if (strlen(input) > 0 && input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }
        else
        {
            errors(INPUT_TOO_LONG);
            while (getchar() != '\n');
            continue;
        }
        
        /*-- Main loop, checks if the user's input is correct --*/

        if (sscanf(input, "%d", &value) != false) /* Convert the STR to INT, prints error if it doesn't work */
        {
            if (value >= 1 && value <= 3) /* Checks if it's a correct number, */
            {
                value--;
                *adrInput = value; /* attributes it to the variable if correct, */
                condition = true;
            }
            else /* prints an error otherwise, asking the user to try again */
            {
                errors(INT_OUT_OF_RANGE);
                continue;
            }
        }
        else
        {
            errors(NON_INT_INPUT);
            continue;
        }
    } while (!condition);
}

/**
 * @brief Have a player takes his turn and play.
 * 
 * @param superGrid Game's grid.
 * @param player The players id, to know if it's 'X'or'O's turn.
 * @param letter Letter used to know the grifd in where the player plays.
*/
void play(struct Grid superGrid[ROW][COLUMN], int player, char letter)
{
    /*-- Finds the indexs of the letter --*/
    int letterRow, letterColumn;
    bool foundLetter = false;
    for (letterRow = 0; letterRow < ROW || !foundLetter; letterRow++)
    {
        for (letterColumn = 0; letterColumn < COLUMN || !foundLetter; letterColumn++)
        {
            if (letter == LETTERS[letterRow][letterColumn])
            {
                foundLetter = true;
            }
        }
    }
    
    /*-- Asks row & column, and checks if it's a correct cell to play in --*/

    bool condition = false;
    int row, column;

    do
    {
        /*-- Asks for row & column, makes it from [1-3] to [0-2] --*/

        printf("Please give the row index: ");
        inputWhichCell(&row);
        row--;
        printf("Please give the column index: ");
        inputWhichCell(&column);
        column--;


        /*-- Checks if the choosen cell is available --*/

        if (superGrid[letterRow][letterColumn].grid[row][column] == '.') /* If it is, changes it to the player's letter */
        {
            if (player == P1)
            {
                superGrid[letterRow][letterColumn].grid[row][column] == 'X'; condition = true;
            } else

            if (player == P2)
            {
                superGrid[letterRow][letterColumn].grid[row][column] == 'O'; condition = true;
            }

            else { errors(PLAYER_ID); } /* In case there somehow is an error with the players' IDs */
        }

        else /* Prints an error otherwise */
        {
            printf("%c", superGrid[letterRow][letterColumn].grid[row][column]); //temp
            errors(CELL_TAKEN);
        }
        
    } while (!condition);
}
