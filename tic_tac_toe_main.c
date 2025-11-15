#include <stdio.h>

// Function to print the Tic-Tac-Toe board
void printBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Function to check if the game is over
int gameOver(char board[3][3]) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
    }
    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return 1;
    }
    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return 1;
    // Check for draw
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return -1; // Game is a draw
}

int main() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int player = 1; // Player 1 starts
    int row, col, move;

    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Player 1: X, Player 2: O\n");

    while (1) {
        printf("\n");
        printBoard(board);
        printf("Player %d, enter your move (row and column): ", player);
        scanf("%d %d", &row, &col);

        if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        if (player == 1) board[row][col] = 'X';
        else board[row][col] = 'O';

        move = gameOver(board);

        if (move == 1) {
            printf("\n");
            printBoard(board);
            printf("Player %d wins!\n", player);
            break;
        } else if (move == -1) {
            printf("\n");
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        player = (player == 1) ? 2 : 1; // Switch players
    }

    return 0;
}
