//Include functions
#include <stdio.h>
#include <ctype.h>

//Global variables

int boardSize = 3;
char board[5][5] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int p1_score = 0;//For player 1 score
int p2_score = 0;//For player 2 score
int player = 1; // Player 1 starts


//Structs

typedef struct 
{
    char p1_symbol;
    char p2_symbol;
} PlayerSymbols;

PlayerSymbols symbols;// Used to scan player symbols

//Function stubs

void displayBoard(char board[5][5], int boardSize);
void chooseBoardSize();//Choose between 3X3,4X4 and 5X5 sizes
void clearBoard();//Clears the board
void menuSystem();//A menu system
void newGame();
void startGame();
int gameOver(char board[5][5], int boardSize);
void displayScoreboard();
void saveGame();
void loadGame();

//Main function
int main() {
    menuSystem();
    return 0;
}

//Function used for displaying the tic-tac-toe board
void displayBoard(char board[5][5], int boardSize) {
    
    printf("\n   ");
    for (int i = 1; i <= boardSize; i++){
        printf(" C%d ", i);
        //This loop is to create column headers(like C1,C2 etc...)
    }
    printf("\n");
    for (int i = 0; i < boardSize; i++) {
        printf(" R%d ", i + 1);//Loop is to create row headers(like R1,R2 etc..)
        for (int j = 0; j < boardSize; j++) {
            printf(" %c ", board[i][j]);
            if (j < boardSize - 1) {
                printf("|");//vertical wall between cells
            }
        }
        printf("\n");
        if (i < boardSize - 1) {
            printf("    ");
            for(int j = 0; j < boardSize; j++) {
                printf("---");//horizontal wall between walls
                if (j < boardSize - 1) {
                    printf("+");//The intersection of horizontal and vertical walls.
                }
            }
            printf("\n");
        }
    }
}

//Function used for choosing Board size.
void chooseBoardSize() {
    int choice;
    printf("Select Board Size: \n");
    printf("1.3X3\n");
    printf("2.4x4\n");
    printf("3.5X5\n");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
        boardSize = 3;
        break;
        case 2:
        boardSize = 4;
        break;
        case 3:
        boardSize = 5;
        break;
        default:
        boardSize = 3;
    }
}

//Function used for clearing the board.
void clearBoard() {
    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize; j++) {
            board[i][j] = ' ';//Replaces the previous symbol with ' '
        }
    }
}

//Function used for creating the menu system.
void menuSystem() {
    
    int row, col, move;
    char test_sym;
    int choice;

    do {
        printf("Menu:\n");
        printf("1.New game\n");
        printf("2.Continue/Load game\n");
        printf("3.Scoreboard\n");
        printf("4.How to play?\n");
        printf("5.Exit\n");

        // This function uses a switch-case statement and calls different functions for different cases.

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                newGame();
                break;
            case 2:
                loadGame();
                break;
            case 3:
                displayScoreboard();
                break;
            case 4:
                printf("Enter the row number and column number to play\n");
                printf("Enter 0 0 in the middle of the game to save the game\n");
                break;
            case 5:
                printf("Exiting the game\n");
                break;
            }
    }while(choice != 5);
}

void newGame() {

    int row, col, move;
    char test_sym;
    char p1_symbol;
    char p2_symbol;
    int choice;

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Players, enter your symbols\n");

do {
    printf("Player 1: ");
    scanf(" %c", &symbols.p1_symbol);
    if (symbols.p1_symbol != 'X' && symbols.p1_symbol != 'O') {
        printf("Invalid symbol! Use X or O.\n");
    }
} while (symbols.p1_symbol != 'X' && symbols.p1_symbol != 'O');// do-while loop to check the validity and scan the symbol entered by player

do {
    printf("Player 2: ");
    scanf(" %c", &symbols.p2_symbol);
    
    if (symbols.p2_symbol != 'X' && symbols.p2_symbol != 'O') {
        printf("Invalid symbol! Use X or O.\n");
    }
    else if (symbols.p2_symbol == symbols.p1_symbol) {
        printf("Player 2 cannot use the same symbol as Player 1!\n");
        symbols.p2_symbol = ' ';  // reset
    }

} while (symbols.p2_symbol != 'X' && symbols.p2_symbol != 'O');// do-while loop to check the validity and scan the symbol entered by player

    chooseBoardSize();
    //You then choose the board size
    clearBoard();
    //Clear the board so that no symbols from the last game will be there.
    startGame();
    //start the actual game.
}

void startGame() {

    int row, col, move;
    char test_sym;
    int choice;

    while (1) {
        printf("\n");
        displayBoard(board, boardSize);
        printf("Player %d, enter your move (row and column): ", player);
        scanf("%d %d", &row, &col);
                    
        if (row == 0 && col == 0) {
            saveGame();// When 0 0 is entered, it saves the game and stops the loop.
            break;
        }
       if (row <= 0 || row > 5 || col <= 0 || col > 5 || board[row - 1][col - 1] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        row--;
        col--;
        //As the index starts from 0 and not 1, we need to subtract 1 from the user-inputted row and column numbers.

        if (player == 1) {
            board[row][col] = symbols.p1_symbol;//Enters the player symbol in the array
        }
        else {
            board[row][col] = symbols.p2_symbol;//Enters the player symbol in the array
        }

        move = gameOver(board, boardSize);//Checks if the game is over or not.

        if (move == 1) {
            printf("\n");
            displayBoard(board, boardSize);
            printf("Player %d wins!\n", player);
            if (player == 1) {
                p1_score++;
            }
            else {
                p2_score++; 
            }
            break;
            } else if (move == -1) {
                printf("\n");
                displayBoard(board, boardSize);
                printf("It's a draw!\n");
                break;
            }

            player = (player == 1) ? 2 : 1;//If the game's not over and the loop continues, this loop switches the player.
    }
}


// Function to check if the game is over
int gameOver(char board[5][5], int boardSize) {

    //Checks if the rows match
    for (int i = 0; i < boardSize; i++) {
        int same = 1;
        for (int j = 1; j < boardSize; j++) {
            if (board[i][j] != board[i][0] || board[i][0] == ' ') {
                same = 0;
                break;
            }
        }
        if (same) return 1;
    }

    //Checks if the columns match 
    for (int j = 0; j < boardSize; j++) {
        int same = 1;
        for (int i = 1; i < boardSize; i++) {
            if (board[i][j] != board[0][j] || board[0][j] == ' ') {
                same = 0;
                break;
            }
        }
        if (same) return 1;
    }

    //Checks if the main diagonal matches or not
    int sameDiag1 = 1;
    for (int i = 1; i < boardSize; i++) {
        if (board[i][i] != board[0][0] || board[0][0] == ' ') {
            sameDiag1 = 0;
            break;
        }
    }
    if (sameDiag1) return 1;

    //Checks if the anti-diagonal matches or not
    int sameDiag2 = 1;
    for (int i = 1; i < boardSize; i++) {
        if (board[i][boardSize - 1 - i] != board[0][boardSize - 1] ||
            board[0][boardSize - 1] == ' ') {
            sameDiag2 = 0;
            break;
        }
    }
    if (sameDiag2) return 1;

    //Checks if it is a draw (no empty spaces)
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (board[i][j] == ' ')
                return 0;  // Game NOT over
        }
    }

    return -1; // Game is draw
}

void displayScoreboard() {
    printf("\n===== SCOREBOARD =====\n");
    printf("Player 1: %d wins\n", p1_score);
    printf("Player 2: %d wins\n", p2_score);
}

void saveGame() {
    FILE *FILE = fopen("savegame.txt", "w");
    if (FILE = "NULL") {
        printf("Failed to open save file for writing.\n");
        return;
    }

    // Format header: boardSize currentPlayer scoreX scoreO
    fprintf(FILE, "%d %d %d %d\n", boardSize, player, p1_score, p2_score);

    // Write board rows exactly boardSize chars per row (spaces allowed)
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            fputc(board[i][j], FILE);
        }
        fputc('\n', FILE);
    }

    fclose(FILE);
    printf("Game saved to savegame.txt\n");
}

void loadGame() {
    FILE *FILE = fopen("savegame.txt", "r");
    if (FILE == NULL) {
        printf("No saved game found (savegame.txt).\n");
        return;
    }

    // Read header
    if (fscanf(FILE, "%d %d %d %d", &boardSize, &player, &p1_score, &p2_score) != 4) {
        printf("Save file corrupted or in wrong format.\n");
        fclose(FILE);
        return;
    }
    int ch = fgetc(FILE);

    // Reads board rows (including spaces)
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            int c = fgetc(FILE);
            if (c == EOF) c = ' ';
            board[i][j] = (char)c;
        }
        // consume newline at end of row if present
        ch = fgetc(FILE);
        if (ch == EOF) break;
    }

    fclose(FILE);
    printf("Game loaded from savegame.txt\n");
    startGame();
}
    return 0;
}

