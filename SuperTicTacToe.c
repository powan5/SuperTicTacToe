/**
 * @brief Program to play Super Tic-Tac-Toe, a variation of tic-tac-toe where players need to complete a grid in order to claim a square of the main grid ('super grid')
 * 
 * @author Powan
 * @version 2.0.1
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* printf("\033[2J\033[1;1H"); // Clears output terminal */

/****************************************************/
/*******|         Constants & Types          |*******/
/****************************************************/

#define CLEAR_TERMINAL "\033[2J\033[1;1H"

#define ROW 3
#define COLUMN 3
#define DIAG 3


typedef struct Grid
{ 
    char grid[ROW][COLUMN]; 
} Grid;

typedef char List[ROW][COLUMN];
const List LETTERS = {
    {'A','B','C'}, 
    {'D','E','F'}, 
    {'G','H','I'}
};

typedef bool ListBool[ROW][COLUMN];

typedef char * gridBlocks[3][9];

typedef char gamertag[46];

enum Players {
    P1 = 1,
    P2 = 2,
    BOT = 2
};

enum error_codes /* There is a logic to it, try to fint it I'll give you a cookie :D */
{
    INPUT_TOO_LONG         = 738476,
    NON_INT_INPUT          = 787373,
    INT_OUT_OF_RANGE       = 737982,
    NON_CHAR_INPUT         = 786773,
    CHAR_INPUT_UNRECONIZED = 677385,
    CELL_TAKEN             = 678475,
    GRID_TAKEN             = 718475,
    PLAYER_ID              = 807368,

    DEBUG                  = 686671,
    UNEXPECTED             = 856984
};

enum choices /* Same logic here for DEFAULT :) */
{
    RULES    = 1,
    MATCH_1P = 2,
    MATCH_2P = 3,
    EXIT     = 0,
    DEFAULT  = 687084
};

enum difficulties /* Same logic here for DEFAULT :) */
{
    EASY     = 1,
    MEDIUM   = 2,
    HARD     = 3,
    MENU     = 0
};

/* For the random name */
const char* vowels[6] = {"a","e","i","o","u","y"};
const char* consonant[20] = {"b","c","d","f","g","h","j","k","l","m","n","p","q","r","s","t","v","w","x","z"};

#define nbOfMemeNames 23
const char* memeNames[23] = {"Pomni", "Xddcc", "PvZGamer", "ElGato", "RickAstley", "BadLuckBrian", "GoodGuyGreg", "Fred", "ForeverAlone", "Pepega", "Area51Raider", "BitcoinMiner", "TheCakeIsALie", "JohnCena", "E", "Shrek", "StonksMan", "Karen","Shaggy","CrazyFrog","LittleRedShit","LampLover","UsernameWasTaken"};

#define nbPrefixes 159
const char* Prefixes[nbPrefixes] = {"1337","Aggro","Alpha","Altered","Ancient","Angel","Anonymous","Aqua","Arcane","Ashen","Assault","Atomic","Awakened","Bad","Baneful","Bio","Bionic","Black","Blade","Blessed","Blood","Bloody","Boosted","Brutal","Buffed","Carnage","Catastrophic","Chaos","Charged","Chrome","Chrono","Combo","Concealed","Consumptive","Corrupted","Creeping","Crimson","Cryptic","Cunning","Cyber","Dark","Darth","Dead","Decimate","Deep","Destructive","Devil","Diamond","Divine","Doom","Dormant","Draconic","Dynamic","Elder","Electro","Elite","Emerald","Enemy","Eon","Epic","Eradicate","Evanescent","Exiled","Fallen","Fatal","Fire","First","Frost","Frozen","Gold","Gosu","Grim","Guerilla","Hardcore","Hate","Hazardous","Hidden","Holy","Icy","Imba","Incendiary","Incognito","Infinite","Invisible","Iron","Killer","Last","Leeroy","Lone","Mad","Majestic","Malefic","Malevolent","Malignant","Master","Menacing","Metal","Mind","Mirror","Mist","Mono","Moon","Murderous","Mystic","Nameless","Necro","Negative","Neo","Nightmare","Nocturnal","Occult","Omnipotent","Panic","Pernicious","Platinum","Prime","Psychic","Quantum","Radical","Radient","Rage","Random","Savage","Secret","Shadow","Silver","Sinister","Sky","Solar","Solid","Solitary","Somber","Soul","Stealth","Steel","Storm","Supernatural","Swift","Terror","Toxic","Tranquil","Transcendent","Treacherous","True","Twisted","Uber","Ultimate","Undercover","Unknowable","Unpredictable","Urban","Veiled","Venom","Vindictive","Virulent","Warp","Wicked","Xeno","Zero"};

#define nbMainName 232
const char* MainName[nbMainName] = {"Aegis","Aether","Agent","Agitator","Alias","Archetype","Archon","Armor","Arrow","Arsenal","Arsonist","Assassin","Assault","Asylum","Atonement","Augur","Aura","Avenger","Axiom","Axon","Battle","Beast","Beastmode","Being","Betrayal","Blade","Blaster","Blaze","Blood","Boss","Burn","Cabal","Cannon","Captain","Carnage","Caster","Cataclysm","Catalyst","Chaos","Chief","Child","Chimera","Clairvoyant","Cloud","Combat","Commander","Crypt","Cut","Cyborg","Damage","Death","Deathmatch","Decay","Decay","Demon","Destruction","Devil","Divinity","Doom","Doppleganger","Dragon","Dragoon","Dream","Dynasty","Edge","Effect","Elder","Elixir","Elysium","Emperor","Empire","Enemy","Enigma","Entity","Epidemic","Equilibrium","Equinox","Eve","Executioner","Exekutioner","Exodus","Explosive","Fatality","Fate","Fire","Firebreath","Flame","Flux","Focus","Force","Freak","Frenzy","Frost","Fury","Fusion","Galaxy","Genesis","Ghost","Glitch","God","Godmode","Grenade","Grimoire","Guard","Guardian","Gun","Hacker","Haxxor","Headshot","Hell","Hellion","Hivemind","Hunter","Hysteria","Impunity","Inferno","Intellect","Juggernaut","Kaos","Killer","Killswitch","Legend","Limit","Lucifer","Machete","Machine","Maelstrom","Master","Mercenary","Mercy","Mind","Mine","Monarch","Monolith","Mood","Moon","Nexus","Night","Nightmare","Ninja","Nuke","Oath","Obelisk","Obliteration","Oblivion","Odyssey","Omen","Omnichrom","Oracle","Outlaw","Overmind","Pain","Panic","Panzer","Paradox","Paragon","Partisan","Planet","Plasma","Priest","Prison","Propaganda","Prophet","Psychosis","Punishment","Pwner","Pyromaniac","Quake","Rachet","Radical","Raid","Raider","Rat","Ray","Razor","Reaper","Rebel","Redshift","Reflux","Requiem","Rhapsody","Ringleader","Rival","Rogue","Root","Rush","Sabotage","Scream","Seeker","Seer","Seizure","Shade","Shooter","Sin","Slash","Slayer","Sniper","Snow","Soul","Space","Spark","Star","Storm","Strategy","Stroke","Tank","Tempest","Terror","Thunder","Titan","Tornado","Trigger","Trinity","Universe","Vehicle","Vengeance","Venom","Venus","Visionary","Void","Voltage","Voodoo","Vortex","Warlock","Warrior","Whisper","Wing","Wizard","Wolf","Zealot","Zephyr","Zone"};

#define nbFlaires 7
const char* Flairs[nbFlaires][2] = {{"xX", "Xx"},{"<<", ">>"},{"-=", "=-"},{"-~", "~-"},{"~*", "*~"},{".:", ":."},{"#*", "*#"}};

#define nbBotNames 15
const char* BotNames[nbBotNames] = {"NoviceBot","SimpleAI","BeginnerMind","SoftSkillBot","EasyGoAI","AdaptiveLogic","BalancedBrain","IntermediateMind","ModestMinds","MiddleGroundAI","ProdigyProcessor","AdvancedAlgorithm","ExpertMind","HardcoreHeuristics","EliteEngineAI"};

/* COLORS YAY */
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"

#define RESET "\x1B[0m"

/****************************************************/
/***|         Prototypes Initialisation          |***/
/****************************************************/

/* Miscellaneous */

void errors(int);
void clearTerminal();
void loading_animation();
void welcome();
void rules();
void namePlayer(char *);
void generateXboxName(char *ptrGamertag);

/* Super Grid & Grids related stuff */

void initSuperGrid(struct Grid superGrid[ROW][COLUMN]);
int gridComplete(struct Grid superGrid[ROW][COLUMN], char);
bool isGridDraw(struct Grid superGrid[ROW][COLUMN], char letter);
int superGridComplete(struct Grid superGrid[ROW][COLUMN]);
void PrintGrid(struct Grid superGrid[ROW][COLUMN]);

/* Inputs */

void inputWhichGrid(char *);
void inputWhichCell(int *);
char takeTurn(struct Grid superGrid[ROW][COLUMN], int, char, int *, int *);

/* Bots */

int setDifficulty();
char easyBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol);
char mediumBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol);
char hardBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol);

/* Main Game Funcitons */

void match1P();
void match2P();
void mainScreen();



/****************************************************/
/**************|         MAIN         |**************/
/****************************************************/

int main()
{
    mainScreen();

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
        case DEBUG: /* Prints a message to know if a set checkpoint has been reached or if the code is broken there */
            printf(RED "Successfully reached checkpoint.\n" RESET );
            break;

        case INPUT_TOO_LONG:
            printf(RED "Error! " RESET "The " MAGENTA "input" RESET " is " MAGENTA "too long" RESET ".\nTry again: \n");
            break;

        case NON_INT_INPUT:
            printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " an " MAGENTA "integer" RESET ".\nTry again: \n");
            break;

        case INT_OUT_OF_RANGE:
            printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " an integer " MAGENTA "between 1 & 3" RESET ".\nTry again: \n");
            break;

        case NON_CHAR_INPUT:
            printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " a " MAGENTA "character" RESET ".\nTry again: \n");
            break;
            
        case CHAR_INPUT_UNRECONIZED:
            printf(RED "Error! " RESET "Please " MAGENTA "input" RESET " a character included " MAGENTA "between A & I" RESET ".\nTry again: \n");
            break;

        case CELL_TAKEN:
            printf(RED "Error! " RESET "That " MAGENTA "cell" RESET " has already been " MAGENTA "claimed" RESET ".\nTry again: \n");
            break;

        case GRID_TAKEN:
            printf(RED "Error! " RESET "That " MAGENTA "grid" RESET " has already been " MAGENTA "claimed" RESET ".\nTry again: \n");
            break;

        case PLAYER_ID: /* If this error is reached, the program can't continue without errors, so exits it before crashing. */
            printf(RED "There was an error with the players' IDs... Exiting"); loading_animation();
            exit(EXIT_FAILURE);
            break;
        
        case UNEXPECTED: /* If this error is reached, a part of the code didn't run properly and a condition wasn't completed even though it should have been (Ex in giveMemeName(){}). */
            printf(RED "Unexpected error... Exiting"); loading_animation();
            exit(EXIT_FAILURE);
            break;

        default: /* This error is not supposed to happen, so exits the program. */
            printf(RED "Error within the errors() function... Exiting"); loading_animation();
            exit(EXIT_FAILURE);
            break;
    }
}

/**
 * @brief clears the terminal screen.
*/
void clearTerminal()
{
    printf(CLEAR_TERMINAL);
}

/**
 * @brief Prints a little loading animation.
*/
void loading_animation()
{
    /* Cuz it looks cool 😎 */
    for (int _ = 0; _ < 3; _++)
    {
        fflush(stdout);
        sleep(1);
        printf(".");
    }
    fflush(stdout);
    sleep(1);
    printf("\n");
}

/**
 * @brief Prints the initial welcome message.
*/
void welcome()
{
    clearTerminal();
    printf(" ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                        By @powan5(dc)\n");
    printf("\n");
    printf("\t\tWELCOME!\n");
    printf("\n");
    printf("\t[1]  Rules\n");
    printf("\t[2]  Start a game (1P)\n");
    printf("\t[3]  Start a match (2P)\n");
    printf("\t[0]  Exit\n");
    printf("\n");
}

/**
 * @brief Prints the rules of the Super Tic-Tac-Toe.
*/
void rules()
{
    clearTerminal();
    printf(" ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                        By @powan5(dc)\n");
    printf("\n");
    printf("                                                                                      \n");
    printf("                                        RULES                                        \n");
    printf("\n");
    printf("The game starts with a move in any of the nine 3x3 grids, chosen by Player 1. (From A to I)\n");
    printf("\n");
    printf("The opponent must play in the corresponding cell of the larger grid, \n");
    printf("based off of in which cell of the small grid the previous player played in.\n");
    printf("\n");
    printf("Winning a small grid awards that grid to the player and determines the opponent's next move.\n");
    printf("\n");
    printf("To win the game, you have to win three small grids in a row horizontally, vertically, or diagonally.\n");
    printf("\n");
    printf("If a player is meant to play in an already won smaller grid,\n");
    printf("they can choose any open cell from any of the available grids.\n");
    printf("\n");
    printf("The game continues until a player wins the larger grid.\n");
    printf("\n");
    printf("If one of the small grid is full but is a draw,\n");
    printf("said grid will be reseted after a turn for players to continue playing.\n");
    printf("\n");
    printf("[Press ENTER to continue] ");
    while (getchar() != '\n');
}

/**
 * @brief Asks the User for a CHAR input, for his pseudo.
 * 
 * @param ptrInput Pointer of the input variable.
*/
void namePlayer(char* ptrInput)
{
    bool condition = false;

    do
    {
        char input[20] = "";

        fgets(input, sizeof(input), stdin);

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

        /*-- Gives the pseudo for the player --*/

        if (input[0] == '*') /* Gets a random pseudo to the player if he so desires */
        {
            gamertag name;
            srand(time(NULL));
            
            int method = rand() % 3;

            switch (method)
            {
                case 0:
                    strcpy(name, consonant[(rand()%19)]);
                    for (int nb = 0; nb < 2; nb++)
                    {
                        strcat(name, vowels[(rand()%5)]);
                        strcat(name, consonant[(rand()%19)]);
                    }

                    name[0] = toupper(name[0]);

                    strcpy(ptrInput, name);
                    condition = true;
                    break;
            
                case 1:
                    strcpy(name, vowels[(rand()%5)]);
                    for (int nb = 0; nb < 2; nb++)
                    {
                        strcat(name, consonant[(rand()%19)]);
                        strcat(name, vowels[(rand()%5)]);
                    }

                    name[0] = toupper(name[0]);

                    strcpy(ptrInput, name);
                    condition = true;
                    break;

                case 2:
                    gamertag xboxGamertag;
                    generateXboxName(xboxGamertag);
                    strcpy(ptrInput, xboxGamertag);
                    condition = true;
                    break;
            
                default:
                    errors(UNEXPECTED);
                    break;
            }

            if ((rand()%100) == 69) /* 1/100 chance of giving a meme name cuz ahah funni :) */
            {
                srand(time(NULL));
                strcpy(ptrInput, memeNames[(rand()%nbOfMemeNames)]);
            }
        }

        else /* Gives the chosen pseudo otherwise */
        {
            strcpy(ptrInput, input);
            condition = true;
        }
    } while (!condition);
}

/**
 * @brief Generate an Xbox-like gamertag.
 * 
 * @returns CHAR*, the generated gamertag.
*/
void generateXboxName(char *ptrGamertag)
{
    gamertag gamertag;
    srand(time(NULL));
    int randomFlair = (rand()%nbFlaires);

    char flair1[3];
    char prefix[20];
    char mainName[20];
    char flair2[3];
    strcpy(flair1, Flairs[randomFlair][0]);
    strcpy(prefix, Prefixes[(rand()%nbPrefixes)]);
    strcpy(mainName, MainName[(rand()%nbMainName)]);
    strcpy(flair2, Flairs[randomFlair][1]);

    strcat(gamertag, flair1);
    strcat(gamertag, prefix);
    strcat(gamertag, mainName);
    strcat(gamertag, flair2);

    strcpy(ptrGamertag, gamertag);
}


/* Super Grid & Grids related stuff */

/**
 * @brief Initialise 'the super grid's grids values with 'Z'.
 * 
 * @param superGrid Game's grid.
*/
void initSuperGrid(struct Grid superGrid[ROW][COLUMN])
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {
            for (int gridRow = 0; gridRow < ROW; gridRow++)
            {
                for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                {
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
 * @returns 1 if Player1 has finished it, 2 if Player2 did, DEFAULT otherwise.
*/
int gridComplete(struct Grid superGrid[ROW][COLUMN], char letter)
{
    int p1_diagL2R, p1_diagR2L, p1_row, p1_col;
    int p2_diagL2R, p2_diagR2L, p2_row, p2_col;

    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {

            /* Finds the index of the current playing grid inside of 'super grid' */
            
            if (letter == LETTERS[row][col]) 
            {
                /*-- Checks the diagonals --*/

                p1_diagL2R = 0, p1_diagR2L = 0, p2_diagL2R = 0, p2_diagR2L = 0;

                for (int diag = 0, invDiag = 2; diag < DIAG; diag++, invDiag--)
                {   
                    /* Checks the diagonal from (0,0) to (2,2) for if P1 won */

                    if (superGrid[row][col].grid[diag][diag] == 'X') 
                    { 
                        p1_diagL2R++;
                    } else

                    /* Checks the diagonal from (0,0) to (2,2) for if P2 won */

                    if (superGrid[row][col].grid[diag][diag] == 'O') 
                    { 
                        p2_diagL2R++; 
                    }

                    /* Checks the diagonal from (0,2) to (2,0) for if P1 won */

                    if (superGrid[row][col].grid[diag][invDiag] == 'X') 
                    { 
                        p1_diagR2L++; 
                    } else

                    /* Checks the diagonal from (0,2) to (2,0) for if P2 won */

                    if (superGrid[row][col].grid[diag][invDiag] == 'O')
                    {
                        p2_diagR2L++;
                    } 
                }

                /*-- Checks the lines (Rows and Columns) --*/

                for (int gridRow = 0; gridRow < ROW; gridRow++)
                {
                    p1_row = 0, p2_row = 0; 
                    p1_col = 0, p2_col = 0;
                    
                    for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                    {

                        /* Checks each rows for if P1 won */

                        if (superGrid[row][col].grid[gridRow][gridCol] == 'X')
                        {
                            p1_row++;
                        } else

                        /* Checks each rows for if P2 won */

                        if (superGrid[row][col].grid[gridRow][gridCol] == 'O')
                        {
                            p2_row++;
                        }

                        /* Checks each columns for if P1 won */

                        if (superGrid[row][col].grid[gridCol][gridRow] == 'X')
                        {
                            p1_col++;
                        } else

                        /* Checks each columns for if P2 won */

                        if (superGrid[row][col].grid[gridCol][gridRow] == 'O')
                        {
                            p2_col++;
                        }

                        /*-- Checks if a player won --*/

                        if (p1_diagR2L == 3 
                        || p1_diagL2R == 3 
                        || p1_row == 3 
                        || p1_col == 3)
                        {
                            return P1;
                        } else

                        if (p2_diagR2L == 3 
                        || p2_diagL2R == 3 
                        || p2_row == 3 
                        || p2_col == 3)
                        {
                            return P2;
                        }
                    }
                }
            }
        }
    }
    return DEFAULT;
}

/**
 * @brief Checks if the given grid inside 'super grid' is full but is a draw.
 * 
 * @param superGrid Game's grid.
 * @param letter Letter of the grid to check, gives the index of said grid.
 * @returns bool, true if the grid is a draw, false otherwise.
*/
bool isGridDraw(struct Grid superGrid[ROW][COLUMN], char letter)
{
    for (int row = 0; row < ROW; row++)
    {
        for (int col = 0; col < COLUMN; col++)
        {
            /* Finds the index of the current playing grid inside of 'super grid' */
            if (letter == LETTERS[row][col]) 
            {
                int nbOfFullCells = 0;

                for (int gridRow = 0; gridRow < ROW; gridRow++)
                {                    
                    for (int gridCol = 0; gridCol < COLUMN; gridCol++)
                    {
                        if (superGrid[row][col].grid[gridRow][gridCol] != '.')
                        {
                            nbOfFullCells++;
                        }
                    }
                }

                if (nbOfFullCells == 9)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Checks if the 'super grid' is completed, so if the game finished.
 * 
 * @param superGrid Game's grid.
 * @returns 1 if Player1 has won, 2 if Player2 did, 0 otherwise.
*/
int superGridComplete(struct Grid superGrid[ROW][COLUMN])
{
    int p1_superDiagL2R, p1_superDiagR2L, p1_superRow, p1_superCol;
    int p2_superDiagL2R, p2_superDiagR2L, p2_superRow, p2_superCol;

    for (int row = 0; row < ROW; row++)
    {
        p1_superRow = 0, p2_superRow = 0;
        p1_superCol = 0, p2_superCol = 0;

        for (int col = 0; col < COLUMN; col++)
        {
            p1_superDiagL2R = 0, p1_superDiagR2L = 0, p2_superDiagL2R = 0, p2_superDiagR2L = 0;
            
            /*-- Checks the diagonals --*/
            for (int diag = 0, invDiag = 2; diag < DIAG; diag++, invDiag--)
            {
                /* Checks the diagonal from (0,0) to (2,2) for if P1 won */

                if (gridComplete(superGrid, LETTERS[diag][diag]) == P1) 
                { 
                    p1_superDiagL2R++;
                } else
                
                /* Checks the diagonal from (0,0) to (2,2) for if P2 won */
                
                if (gridComplete(superGrid, LETTERS[diag][diag]) == P2) 
                { 
                    p2_superDiagL2R++;
                } 
                
                /* Checks the diagonal from (0,2) to (2,0) for if P1 won */

                if (gridComplete(superGrid, LETTERS[diag][invDiag]) == P1) 
                { 
                    p1_superDiagR2L++; 
                } else
                
                /* Checks the diagonal from (0,2) to (2,0) for if P2 won */
                
                if (gridComplete(superGrid, LETTERS[diag][invDiag]) == P2) 
                {
                    p2_superDiagR2L++;
                }
            }

            /*-- Checks the lines (Rows and Columns) --*/
            
            /* Checks each rows for if P1 won */

            if (gridComplete(superGrid, LETTERS[row][col]) == P1) 
            {
                p1_superRow++;
            } else
            
            /* Checks each rows for if P2 won */

            if (gridComplete(superGrid, LETTERS[row][col]) == P2) 
            {
                p2_superRow++;
            }
            
            /* Checks each columns for if P1 won */
            
            if (gridComplete(superGrid, LETTERS[col][row]) == P1) 
            {
                p1_superCol++;
            } else
            
            /* Checks each columns for if P2 won */

            if (gridComplete(superGrid, LETTERS[col][row]) == P2) 
            { 
                p2_superCol++;
            }

            /*-- Checks if a player won --*/

            if (p1_superDiagL2R == 3 || p1_superDiagR2L == 3 || p1_superRow == 3 || p1_superCol == 3)
            {
                return P1;
            } else

            if (p2_superDiagL2R == 3 || p2_superDiagR2L == 3 || p2_superRow == 3 || p2_superCol == 3)
            {
                return P2;
            }
        }
    }
    return DEFAULT;
}

/**
 * @brief Prints the game's grid in the terminal.
 * 
 * @param superGrid Game's grid.
*/
void PrintGrid(struct Grid superGrid[ROW][COLUMN])
{
    clearTerminal();

    /*-- Output template --*/

    gridBlocks BLOCS = {
        { /* Main grid */
        YELLOW "|" GREEN " %c  " CYAN " 1   2   3 " GREEN "  %c " RESET,
        YELLOW "|" BLUE  "   +---+---+---+   " RESET,
        YELLOW "| 1 | %c | %c | %c | 1 ",
        YELLOW "|" BLUE  "   +---+---+---+   " RESET,
        YELLOW "| 2 | %c | %c | %c | 2 ",
        YELLOW "|" BLUE  "   +---+---+---+   " RESET,
        YELLOW "| 3 | %c | %c | %c | 3 ",
        YELLOW "|" BLUE  "   +---+---+---+   " RESET,
        YELLOW "|" GREEN " %c  " CYAN  " 1   2   3 " GREEN "  %c "},
        { /* Grid completed by P1 */
        YELLOW "| " RED "                  " RESET,
        YELLOW "| " RED "                  " RESET,
        YELLOW "| " RED "      \\   /       " RESET,
        YELLOW "| " RED "       \\ /        " RESET,
        YELLOW "| " RED "        X         " RESET,
        YELLOW "| " RED "       / \\        " RESET,
        YELLOW "| " RED "      /   \\       " RESET,
        YELLOW "| " RED "                  " RESET,
        YELLOW "| " RED "                  " RESET},
        { /* Grid completed by P2 */
        YELLOW "| " BLUE "                  " RESET,
        YELLOW "| " BLUE "                  " RESET,
        YELLOW "| " BLUE "    /-------\\     " RESET,
        YELLOW "| " BLUE "    |       |     " RESET,
        YELLOW "| " BLUE "    |       |     " RESET,
        YELLOW "| " BLUE "    |       |     " RESET,
        YELLOW "| " BLUE "    \\-------/     " RESET,
        YELLOW "| " BLUE "                  " RESET,
        YELLOW "| " BLUE "                  " RESET}
        };


    /**-- Main loop --*/
    for (int superRow = 0; superRow < ROW; superRow++)
    {
        printf(YELLOW "+-------------------+-------------------+-------------------+\n"); /* Dividers for the 'super grid' */
        for (int blocRowIndex = 0; blocRowIndex < 9; blocRowIndex++)
        {
            for (int superCol = 0; superCol < COLUMN; superCol++)
            {
                switch (gridComplete(superGrid, LETTERS[superRow][superCol])) /* Checks if a player has won a square of the 'super grid' or not */
                {
                    /* Prints the square if a player has won it */
                    case P1:
                        printf("%s", BLOCS[P1][blocRowIndex]);
                        break;
                    
                    case P2:
                        printf("%s", BLOCS[P2][blocRowIndex]);
                        break;

                    /* Prints the square if neither of the players has won it */
                    default:
                        if (blocRowIndex == 0 || blocRowIndex == 8) /* "| %c   1   2   3   %c |" */
                        {
                            char printableLine[70] = "";
                            sprintf(printableLine, BLOCS[0][blocRowIndex], LETTERS[superRow][superCol], LETTERS[superRow][superCol]);
                            printf("%s", printableLine);
                            break; 
                        } else
                        
                        if (blocRowIndex == 1 || blocRowIndex == 3 || blocRowIndex == 5 || blocRowIndex == 7) /* "|   +---+---+---+   |" */
                        {
                            printf("%s", BLOCS[0][blocRowIndex]); 
                            break; 
                        }

                        else /* "| [nb] | %c | %c | %c | [nb] |" */
                        {
                            printf(YELLOW "| " CYAN "%d " RESET, (blocRowIndex/2));

                            for (int tinyCol = 0; tinyCol < COLUMN; tinyCol++)
                            {
                                printf(BLUE "| " RESET "%c ", superGrid[superRow][superCol].grid[(blocRowIndex/2)-1][tinyCol]);
                            }

                            printf(BLUE "| " CYAN "%d ", blocRowIndex/2);
                            break;
                        }
                        break;
                }
            }
            printf( YELLOW "|\n" RESET);
        }
    }
    printf(YELLOW "+-------------------+-------------------+-------------------+\n\n" RESET);
}


/* Inputs */

/**
 * @brief Asks the User for a CHAR input in order to choose where to play in the 'super grid'.
 * 
 * @param ptrInput Pointer of the input variable.
*/
void inputWhichGrid(char *ptrLetter)
{
    printf("In which grid do you wish to play (From 'A' to 'I'): \n");
    
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
                    *ptrLetter = upperInput;
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
 * @param ptrInput Pointer of the input variable.
*/
void inputWhichCell(int *ptrInput)
{
    printf("(From 1 to 3): \n");
    
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
                *ptrInput = value; /* attributes it to the variable if correct, */
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
 * @brief Have a player take his turn and play.
 * 
 * @param superGrid Game's grid.
 * @param player The players id, to know if it's 'X'or'O's turn.
 * @param letter Letter used to know the grifd in where the player plays.
 * @param ptrPlayerRow Pointer of the row where the player plays.
 * @param ptrPlayerCol Pointer of the column where the player plays.
 * 
 * @returns CHAR, letter for the next player to play in.
*/
char takeTurn(struct Grid superGrid[ROW][COLUMN], int player, char letter, int *ptrPlayerRow, int *ptrPlayerCol)
{
    /*-- Finds the indexs of the letter --*/
    int superGridRow, superGridColumn;

    bool foundLetter = false;
    int letterRow = 0, letterColumn = 0;
    while (letterRow < ROW || !foundLetter)
    {
        while (letterColumn < COLUMN || !foundLetter)
        {
            if (letter == LETTERS[letterRow][letterColumn])
            {
                foundLetter = true;
                superGridRow = letterRow;
                superGridColumn = letterColumn;
            }
            letterColumn++;
        }
        letterRow++;
    }
    
    
    /*-- Asks row & column, and checks if it's a correct cell to play in --*/

    bool turnCompleted = false;
    int row = -1, column = -1;

    do
    {
        /*-- Asks for row & column, makes it from [1-3] to [0-2] --*/

        printf("Please give the row index ");
        inputWhichCell(&row);
        printf("Please give the column index ");
        inputWhichCell(&column);

        /*-- Checks if the chosen cell is available --*/

        if (superGrid[superGridRow][superGridColumn].grid[row][column] == '.') /* If it is, changes it to the player's letter */
        {
            

            if (player == P1)
            {
                /* X */
                *ptrPlayerRow = row;
                *ptrPlayerCol = column;
                turnCompleted = true;

            } else

            if (player == P2)
            {
                /* O */
                *ptrPlayerRow = row;
                *ptrPlayerCol = column;
                turnCompleted = true;
            }
            
            else /* In case there somehow is an error with the players' IDs */
            { 
                errors(PLAYER_ID); 
            }
        }

        else /* Prints an error otherwise */
        {
            errors(CELL_TAKEN);
        }
    } while (!turnCompleted);

    return LETTERS[row][column];
}


/* Bot Functions */

/**
 * @brief Sets the difficulty of the bot via a menu.
 * 
 * @returns INT, the difficulty of the bot.
*/
int setDifficulty()
{
    int choice = DEFAULT;

    clearTerminal();
    printf(" ____  _  _  ____  ____  ____    ____  __  ___     ____  __    ___     ____  __  ____ \n");
    printf("/ ___)/ )( \\(  _ \\(  __)(  _ \\  (_  _)(  )/ __)___(_  _)/  \\  / __)___(_  _)/  \\(  __)\n");
    printf("\\___ \\) \\/ ( ) __/ ) _)  )   /    )(   )(( (__(___) )( /    \\( (__(___) )( (    )) _) \n");
    printf("(____/\\____/(__)  (____)(__\\_)   (__) (__)\\___)    (__)\\_/\\_/ \\___)    (__) \\__/(____)\n");
    printf("                                                                        By @powan5(dc)\n");
    printf("\n");
    printf("                                                                                      \n");
    printf("                      Weclome to a 1 Player match against a bot                      \n");
    printf("\n");
    printf("Please select a difficulty: \n");
    printf("\n");
    printf("\t[1]  Easy (Makes fully random moves)\n");
    printf("\t[2]  Medium (1/3 chance of making the most advantageous move, random otherwise)\n");
    printf("\t[3]  Hard (Makes only the most advantageous mouves)\n");
    printf("\t[0]  Main menu\n");
    printf("\n");

    do
    {
        scanf("%d", &choice);        
    } while (choice != EASY && choice!= MEDIUM && choice!= HARD && choice!= MENU);

    return choice;
}

/**
 * @brief Have the bot take its turn and play RANDOMLY.
 * 
 * @param superGrid Game's grid.
 * @param letter Letter used to know the grid in which the bot plays.
 * @param ptrBotRow Pointer to store the row index of the bot's move.
 * @param ptrBotCol Pointer to store the column index of the bot's move.
*/
char easyBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol)
{
    clearTerminal();
    printf("Thinking");
    loading_animation();

    /* Get available cells */
    int availableCells[9];
    int count = 0;

    /* Finds the current playing grid */ 
    bool foundLetter = false;
    int superGridRow, superGridColumn;

    for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
    {
        for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
        {
            if (letter == LETTERS[letterRow][letterColumn])
            {
                foundLetter = true;
                superGridRow = letterRow;
                superGridColumn = letterColumn;
            }
        }
    }

    /* Finds available cells */
    for(int gridRow = 0; gridRow < ROW; gridRow++)
    {
        for(int gridCol = 0; gridCol < COLUMN; gridCol++)
        {
            if(superGrid[superGridRow][superGridColumn].grid[gridRow][gridCol] == '.')
            {
                availableCells[count] = gridRow*COLUMN + gridCol;
                count++;
            }
        }
    }

    /* Choose random available cell */
    srand(time(NULL));
    int randIndex = rand() % count;
    int chosenRow = availableCells[randIndex] / COLUMN;
    int chosenCol = availableCells[randIndex] % COLUMN;

    /* Plays the turn */
    *ptrBotRow = chosenRow;
    *ptrBotCol = chosenCol;

    return LETTERS[chosenRow][chosenCol];
}

/**
 * @brief Have the bot take its turn and play a move, either easy or hard.
 * 
 * @param superGrid Game's grid.
 * @param letter Letter used to know the grid in which the bot plays.
 * @param ptrBotRow Pointer to store the row index of the bot's move.
 * @param ptrBotCol Pointer to store the column index of the bot's move.
 * 
*/
char mediumBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol)
{
    clearTerminal();
    printf("Thinking");
    loading_animation();

    srand(time(NULL));

    int choice = rand() % 3;

    switch (choice)
    {
        case 1:
            return hardBotTurn(superGrid, letter, ptrBotRow, ptrBotCol);
            break;
        
        default:
            return easyBotTurn(superGrid, letter, ptrBotRow, ptrBotCol);
            break;
    }
}

/**
 * @brief Have the bot take its turn and play the best move.
 * 
 * @param superGrid Game's grid.
 * @param letter Letter used to know the grid in which the bot plays.
 * @param ptrBotRow Pointer to store the row index of the bot's move.
 * @param ptrBotCol Pointer to store the column index of the bot's move.
 * 
*/
char hardBotTurn(struct Grid superGrid[ROW][COLUMN], char letter, int *ptrBotRow, int *ptrBotCol)
{
    clearTerminal();
    printf("Thinking");
    loading_animation();

    int choosenRow = 0, choosenCol = 0;

    /* Finds the current playing grid */
    bool foundLetter = false;
    int superGridRow, superGridColumn;
    for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
    {
        for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
        {
            if (letter == LETTERS[letterRow][letterColumn])
            {
                foundLetter = true;
                superGridRow = letterRow;
                superGridColumn = letterColumn;
            }
        }
    }

    /* Choose a tactical available cell */
    bool foundCell = false;
    
    /*-- Checks if a player is close to winning --*/
    while (!foundCell)
    {
        /*-- Checks the lines (Rows and Columns) --*/
        for (int row = 0; row < ROW; row++)
        {
            for (int col = 0; col < COLUMN; col++)
            {
                /* Checks the row for if P2 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'O')
                {
                    int p2_row = 0;
                    for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == 'O')
                        {
                            p2_row++;
                        }
                        if (p2_row == 2)
                        {
                            for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == '.')
                                {
                                    choosenRow = rowCheck;
                                    choosenCol = col;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }

                /* Checks the column for if P2 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'O')
                {
                    int p2_col = 0;
                    for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == 'O')
                        {
                            p2_col++;
                        }
                        if (p2_col == 2)
                        {
                            for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == '.')
                                {
                                    choosenRow = row;
                                    choosenCol = colCheck;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }

                /* Checks the row for if P1 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'X')
                {
                    int p1_row = 0;
                    for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == 'X')
                        {
                            p1_row++;
                        }
                        if (p1_row == 2)
                        {
                            for (int rowCheck = 0; rowCheck < ROW; rowCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[rowCheck][col] == '.')
                                {
                                    choosenRow = rowCheck;
                                    choosenCol = col;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }

                /* Checks the column for if P1 is close to winning */
                if (superGrid[superGridRow][superGridColumn].grid[row][col] == 'X')
                {
                    int p1_col = 0;
                    for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                    {
                        if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == 'X')
                        {
                            p1_col++;
                        }
                        if (p1_col == 2)
                        {
                            for (int colCheck = 0; colCheck < COLUMN; colCheck++)
                            {
                                if (superGrid[superGridRow][superGridColumn].grid[row][colCheck] == '.')
                                {
                                    choosenRow = row;
                                    choosenCol = colCheck;
                                    foundCell = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        /*-- Checks the lines (Diagonals) --*/
        for (int diag = 0, invDiag = 2; diag < DIAG; diag++, invDiag--)
        {
            /* Checks the diagonal from (0,0) to (2,2) for if P2 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][diag] == 'O')
            {
                int p2_diagL2R = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == 'O')
                    {
                        p2_diagL2R++;
                    }
                    if (p2_diagL2R == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == '.')
                            {
                                choosenRow = diagCheck;
                                choosenCol = diagCheck;
                                foundCell = true;
                            }
                        }
                    }
                }
            }

            /* Checks the diagonal from (0,2) to (2,0) for if P2 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][invDiag] == 'O')
            {
                int p2_diagR2L = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == 'O')
                    {
                        p2_diagR2L++;
                    }
                    if (p2_diagR2L == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == '.')
                            {
                                choosenRow = diagCheck;
                                choosenCol = invDiag;
                                foundCell = true;
                            }
                        }
                    }
                }
            }

            /* Checks the diagonal from (0,0) to (0,0) for if P1 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][diag] == 'X')
            {
                int p1_diagL2R = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == 'X')
                    {
                        p1_diagL2R++;
                    }
                    if (p1_diagL2R == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][diagCheck] == '.')
                            {
                                choosenRow = diagCheck;
                                choosenCol = diagCheck;
                                foundCell = true;
                            }
                        }
                    }
                }
            }

            /* Checks the diagonal from (0,2) to (0,2) for if P1 is close to winning */
            if (superGrid[superGridRow][superGridColumn].grid[diag][invDiag] == 'X')
            {
                int p1_diagR2L = 0;
                for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == 'X')
                    {
                        p1_diagR2L++;
                    }
                    if (p1_diagR2L == 2)
                    {
                        for (int diagCheck = 0; diagCheck < DIAG; diagCheck++)
                        {
                            if (superGrid[superGridRow][superGridColumn].grid[diagCheck][invDiag] == '.')
                            {
                                choosenRow = diagCheck;
                                choosenCol = invDiag;
                                foundCell = true;
                            }
                        }
                    }
                }
            }
        }
        if (!foundCell)
        {
            /* If no winning/counter cells were found, checks for tactical moves */
            for (int row = 0; row < ROW; row++)
            {
                for (int col = 0; col < COLUMN; col++)
                {
                    if (superGrid[superGridRow][superGridColumn].grid[1][1] == '.')
                    {
                        choosenRow = 1;
                        choosenCol = 1;
                        foundCell = true;
                    } else

                    if (superGrid[superGridRow][superGridColumn].grid[0][0] == '.')
                    {
                        choosenRow = 0;
                        choosenCol = 0;
                        foundCell = true;
                    } else

                    if (superGrid[superGridRow][superGridColumn].grid[0][2] == '.')
                    {
                        choosenRow = 0;
                        choosenCol = 2;
                        foundCell = true;
                    } else
                    
                    if (superGrid[superGridRow][superGridColumn].grid[2][0] == '.')
                    {
                        choosenRow = 2;
                        choosenCol = 0;
                        foundCell = true;
                    } else

                    if (superGrid[superGridRow][superGridColumn].grid[2][2] == '.')
                    {
                        choosenRow = 2;
                        choosenCol = 2;
                        foundCell = true;
                    }

                    if (foundCell)
                    {
                        printf("AHAH! I've found a tactical move!\n");
                        printf("I'm going to make a move at (%d, %d)!\n", choosenRow, choosenCol);
                    }
                    
                    
                    else
                    {
                        /* If no tactical moves were found, Makes a random move */
                        easyBotTurn(superGrid, letter, ptrBotRow, ptrBotCol);
                        foundCell = true;
                    }
                }
            }
        }
    }

    /* Playes the turn */
    *ptrBotRow = choosenRow;
    *ptrBotCol = choosenCol;

    return LETTERS[choosenRow][choosenCol];
}

/**
 * @brief Have the bot choose a letter.
 * 
 * @param superGrid The grid to check for taken cells.
 * @param ptrLetter The letter to be chosen.
*/
void botChooseLetter(struct Grid superGrid[ROW][COLUMN] , char *ptrLetter)
{
    do
    {
        srand(time(NULL));
        int randRow = rand() % ROW;

        fflush(stdout);
        sleep(1);

        srand(time(NULL));
        int randCol = rand() % COLUMN;

        ptrLetter = LETTERS[randRow][randCol];

        fflush(stdout);
        sleep(1);
        printf(".");
    } while (!gridComplete(superGrid, ptrLetter));

}

/****************************************************/
/******|         Main Game Functions          |******/
/****************************************************/

/**
 * @brief Runs a single player match against a BOT opponent.
*/
void match1P()
{
    clearTerminal();

    int difficulty = setDifficulty();

    if (difficulty == MENU)
    {
        mainScreen();
    }

    char rematch = 'N';
    int player = 1, playedRow = 0, playedCol = 0;
    int turns = 0;
    char letter = 'Z';
    int winCondition = DEFAULT;

    struct Grid superGrid[ROW][COLUMN];
    initSuperGrid(superGrid);

    /* Get the pseudo for the players & bot */
    gamertag playerName;
    gamertag botName;

    while (getchar() != '\n'); /* Clears entry buffer */
    printf("Player, please choose you pseudo ('*' for a random one): \n");
    namePlayer(playerName);

    /* Get the pseudo for the bot */
    srand(time(NULL));
    int botPseudo = rand() % (nbBotNames/3);
    switch (difficulty)
    {
        case EASY:
            strcpy(botName, BotNames[botPseudo]);
            break;

        case MEDIUM:
            strcpy(botName, BotNames[botPseudo+5]);
            break;

        case HARD:
            strcpy(botName, BotNames[botPseudo+10]);
            break;
        
        default:
            errors(UNEXPECTED);
            break;
    }

    printf("%s will play 'X'\n", playerName);
    printf("%s will play 'O'\n", botName);

    fflush(stdout);
    sleep(5);

    do
    {
        turns++;

        fflush(stdout);
        PrintGrid(superGrid);

        /* Checks which player's turn it is */
        if (player == P1) { printf(RED "%s" RESET "(X) to play, ", playerName); }
        else if (player == P2) { printf(RED "%s" RESET "(O) to play, ", botName); }

        /* If the game has just started */
        if (letter == 'Z')
        {
            inputWhichGrid(&letter);
        } else

        /* If the supposed grid to play in is completed */
        if (gridComplete(superGrid, letter) != DEFAULT) 
        {
            printf("The supposed grid already full, so ");
            if (player == P1) { inputWhichGrid(&letter); }
            else if (player == P2)
            {
                printf("I'm going to play in ");
                botChooseLetter(superGrid, &letter);
                printf(" the '%c' grid.\n", letter);
            }

            while (gridComplete(superGrid, letter) != DEFAULT)
            {
                errors(GRID_TAKEN);
                inputWhichGrid(&letter);
            }
        }

        /* Reminds which grid the player is in */
        else
        {
            printf("\nYou are playing in the '%c' grid.\n\n", letter);
        }

        /* Finds the letter indexs */
        bool foundLetter = false;
        int superGridRow, superGridColumn;

        for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
        {
            for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
            {
                if (letter == LETTERS[letterRow][letterColumn])
                {
                    foundLetter = true;
                    superGridRow = letterRow;
                    superGridColumn = letterColumn;
                }
            }
        }

        if (player == P1)
        {
            letter = takeTurn(superGrid, player, letter, &playedRow, &playedCol);
        } else

        if (player == P2)
        {
            switch (difficulty)
            {
                case EASY:
                    letter = easyBotTurn(superGrid, letter, &playedRow, &playedCol);
                    break;

                case MEDIUM:
                    letter = mediumBotTurn(superGrid, letter, &playedRow, &playedCol);
                    break;
                
                case HARD:
                    letter = hardBotTurn(superGrid, letter, &playedRow, &playedCol);
                    break;
                
                default:
                    errors(UNEXPECTED);
                    break;
            }
        }

        /* If the grid got full but not won by any, resets it after the next player's turn */
        if(isGridDraw(superGrid, letter))
        {
            for (int row = 0; row < ROW; row++)
            {
                for (int col = 0; col < COLUMN; col++)
                {
                    superGrid[superGridRow][superGridColumn].grid[row][col] = '.';
                }
            }
        }

        /* Takes care of asigning the correct player's symbol and switching players */
        switch (player)
        {
            case P1:
                superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'X';
                player = P2;
                break;
        
            case BOT:
                superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'O';
                player = P1;
                break;

            default:
                errors(PLAYER_ID);
                break;
        }

        /* Checks if the game has been won */
        winCondition = superGridComplete(superGrid);
    }while (winCondition == DEFAULT);

    PrintGrid(superGrid);
    printf("You played for %d turns.\n", turns);

    printf("Do you want to play again ? [Y]/[N] ");
    scanf("%c", &rematch);
    rematch = toupper(rematch);
    if (rematch == 'Y')
    {
        clearTerminal();
        printf("Reinitialising");
        loading_animation();
        match1P();
    }
}

/**
 * @brief Runs a 2 player match with alternating turns.
*/
void match2P()
{
    clearTerminal();

    char rematch = 'N';
    int player = 1, playedRow = 0, playedCol = 0;
    int turns = 0;
    char letter = 'Z';
    int winCondition = DEFAULT;

    struct Grid superGrid[ROW][COLUMN]; 
    initSuperGrid(superGrid);

    /* Get the pseudo for both players */
    gamertag nameP1;
    gamertag nameP2;

    while (getchar() != '\n'); /* Clears entry buffer */
    printf("Player 1, please choose you pseudo ('*' for a random one): \n");
    namePlayer(nameP1);
    sleep(1);
    printf("Player 2, please choose you pseudo ('*' for a random one): \n");
    namePlayer(nameP2);


    printf("%s will play 'X' & ", nameP1);
    printf("%s will play 'O'\n", nameP2);

    fflush(stdout);
    sleep(5);

    do
    {
        turns++;

        fflush(stdout);
        PrintGrid(superGrid);

        /* Checks which player's turn it is */
        if (player == P1) { printf(RED "%s" RESET "(X) to play, ", nameP1); }
        else if (player == P2) { printf(RED "%s" RESET "(O) to play, ", nameP2); }                    

        /* If the game has just started */
        if (letter == 'Z')
        {
            inputWhichGrid(&letter);
        } else
        
        /* If the supposed grid to play in is completed */
        if (gridComplete(superGrid, letter) != DEFAULT) 
        {
            printf("The supposed grid already full, so ");
            inputWhichGrid(&letter);
            
            while (gridComplete(superGrid, letter) != DEFAULT)
            {
                errors(GRID_TAKEN);
                inputWhichGrid(&letter);
            }
        }

        /* Reminds which grid the player is in */
        else
        {
            printf("\nYou are playing in the '%c' grid.\n\n", letter);
        }

        /* Finds the letter indexs */
        bool foundLetter = false;
        int superGridRow, superGridColumn;

        for (int letterRow = 0; letterRow < ROW && !foundLetter; letterRow++)
        {
            for (int letterColumn = 0; letterColumn < COLUMN && !foundLetter; letterColumn++)
            {
                if (letter == LETTERS[letterRow][letterColumn])
                {
                    foundLetter = true;
                    superGridRow = letterRow;
                    superGridColumn = letterColumn;
                }
            }
        }
        

        letter = takeTurn(superGrid, player, letter, &playedRow, &playedCol);

        /* If the grid got full but not won by any, resets it after the next player's turn */
        if(isGridDraw(superGrid, letter))
        {
            for (int row = 0; row < ROW; row++)
            {
                for (int col = 0; col < COLUMN; col++)
                {
                    superGrid[superGridRow][superGridColumn].grid[row][col] = '.';
                }
            }
        }

        /* Takes care of asigning the correct player's symbol and switching players */
        switch (player)
        {
            case P1:
                superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'X';
                player = P2;
                break;
        
            case P2:
                superGrid[superGridRow][superGridColumn].grid[playedRow][playedCol] = 'O';
                player = P1;
                break;

            default:
                errors(PLAYER_ID);
                break;
        }

        /* Checks if the game has been won */
        winCondition = superGridComplete(superGrid);
    } while (winCondition == DEFAULT);

    PrintGrid(superGrid);
    printf("You played for %d turns.\n", turns);
    
    printf("Do you want to play again ? [Y]/[N] ");
    scanf("%c", &rematch);
    rematch = toupper(rematch);
    if (rematch == 'Y')
    {
        clearTerminal();
        printf("Reinitialising");
        loading_animation();
        match2P();
    }
}

/**
 * @brief Main function, runs the game.
*/
void mainScreen()
{
    /*-- Variables --*/
    int choice = DEFAULT;

    welcome();


    /*-- Main loop --*/

    do
    {
        printf("Please input your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            /*-- Exit --*/
            case EXIT:
                printf("Exiting");
                loading_animation();
                exit(EXIT_SUCCESS);
                break;

            /****************************************************/
            /**************|         Rules        |**************/
            /****************************************************/    

            case RULES:
                char PressEnterToContinue = 0;
                rules();
                while (PressEnterToContinue != '\r' && PressEnterToContinue != '\n') { PressEnterToContinue = getchar(); }
                choice = DEFAULT;
                welcome();
                break;

            /****************************************************/
            /*************|     1 Player match     |*************/
            /****************************************************/

            case MATCH_1P:
                clearTerminal();
                printf("Initialising");
                loading_animation();

                match1P();

                choice = DEFAULT;
                welcome();
                break;

            /****************************************************/
            /**************|    2 Players match    |*************/
            /****************************************************/

            case MATCH_2P:
                clearTerminal();
                printf("Initialising");
                loading_animation();

                match2P(); /* Calls the 2P match function that does it all */

                choice = DEFAULT;
                welcome();
                break;
            
            default:
                choice = DEFAULT;
                welcome();
                break;
        }

    } while (choice == DEFAULT);
}
