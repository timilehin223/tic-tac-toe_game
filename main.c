#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int selectGameMode() {
    char gameModeChoice;
    while (1) {
        printf("Select a Game Mode:\n");
        printf("A. Human VS Computer\n");
        printf("B. Human VS Human\n");
        printf("Insert A or B: ");
        scanf(" %c", &gameModeChoice);
        if (gameModeChoice != 'A' && gameModeChoice != 'B') {
            printf("Invalid Choice. Please pick between A and B.\n");
        } else {
            return (gameModeChoice == 'A') ? 0 : 1;
        }
    }
}

void initializeGrid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = ' ';
        }
    }
}

void drawGrid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("[%c]", grid[i][j]);
        }
        printf("\n");
    }
}

void handlePlayerMove(char grid[3][3], char currentPlayer, char *currentPlayerName) {
    int row, col;
    while (1) {
        printf("%s, enter row and column (0-2): ", currentPlayerName);
        int result = scanf("%d %d", &row, &col);

        if (result != 2 || row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Invalid move. Row and column must be between 0 and 2.\n");
            continue;
        }

        if (grid[row][col] != ' ') {
            printf("Cell already occupied. Try again.\n");
            continue;
        }

        grid[row][col] = currentPlayer;
        break;
    }
}

bool checkWin(char grid[3][3], char currentPlayer) {
    for (int i = 0; i < 3; i++) {
        if ((grid[i][0] == currentPlayer && grid[i][1] == currentPlayer && grid[i][2] == currentPlayer) ||
            (grid[0][i] == currentPlayer && grid[1][i] == currentPlayer && grid[2][i] == currentPlayer)) {
            return true;
            }
    }
    if ((grid[0][0] == currentPlayer && grid[1][1] == currentPlayer && grid[2][2] == currentPlayer) ||
        (grid[0][2] == currentPlayer && grid[1][1] == currentPlayer && grid[2][0] == currentPlayer)) {
        return 1;
        }
    return 0;
}

void playHumanVsHuman() {
    char grid[3][3];
    initializeGrid(grid);

    char playerX[20], playerO[20];
    printf("Player 1 (X), insert your Username:\n");
    scanf("%19s", playerX);
    printf("Player 2 (O), insert your Username:\n");
    scanf("%19s", playerO);
    printf("Welcome %s and %s\n", playerX, playerO);

    char currentPlayer = 'X';
    char *currentPlayerName = playerX;
    int moves = 0;

    while (1) {
        handlePlayerMove(grid, currentPlayer, currentPlayerName);
        moves++;

        if (checkWin(grid, currentPlayer)) {
            drawGrid(grid);
            printf("Congratulations %s! You have won!\n", currentPlayerName);
            break;
        }

        if (moves == 9) {
            drawGrid(grid);
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        if (currentPlayer == 'X') {
            currentPlayer = 'O';
            currentPlayerName = playerO;
        } else {
            currentPlayer = 'X';
            currentPlayerName = playerX;
        }
    }
}

int selectDifficulty() {
    char level;
    while (1) {
        printf("Select a difficulty:\n");
        printf("A. Easy\nB. Medium\nC. Difficult\n");
        scanf(" %c", &level);
        if (level == 'A') return 0;
        if (level == 'B') return 1;
        if (level == 'C') return 2;
        printf("Invalid Choice. Please pick between A, B, and C.\n");
    }
}

void playHumanVsComputerEasy(char grid[3][3], char *human) {
    char currentPlayer = 'X';
    int moves = 0;
    srand(time(0));

    while (1) {
        if (currentPlayer == 'X') {
            handlePlayerMove(grid, currentPlayer, human);
        } else {
            int row, col;
            do {
                row = rand() % 3;
                col = rand() % 3;
            } while (grid[row][col] != ' ');

            printf("Computer chooses: %d %d\n", row, col);
            grid[row][col] = 'O';
        }

        drawGrid(grid);
        moves++;

        if (checkWin(grid, currentPlayer)) {
            if (currentPlayer == 'X') {
                printf("Congratulations %s! You have won!\n", human);
            } else {
                printf("Computer wins!\n");
            }
            break;
        }

        if (moves == 9) {
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

bool findWinningMove(char grid[3][3], char symbol, int *row, int *col) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                grid[i][j] = symbol;
                if (checkWin(grid, symbol)) {
                    *row = i;
                    *col = j;
                    return true;
                }
                grid[i][j] = ' ';
            }
        }
    }
    return false;
}

void playHumanVsComputerMedium(char grid[3][3], char *human) {
    char currentPlayer = 'X';
    int moves = 0;
    srand(time(0));

    while (1) {
        if (currentPlayer == 'X') {
            handlePlayerMove(grid, currentPlayer, human);
        } else {
            int row, col;
            if (findWinningMove(grid, 'O', &row, &col)) {
                grid[row][col] = 'O';
                printf("Computer chooses: %d %d\n", row, col);
            } else if (findWinningMove(grid, 'X', &row, &col)) {
                grid[row][col] = 'O';
                printf("Computer chooses: %d %d\n", row, col);
            } else {
                do {
                    row = rand() % 3;
                    col = rand() % 3;
                } while (grid[row][col] != ' ');

                printf("Computer chooses: %d %d\n", row, col);
                grid[row][col] = 'O';
            }
        }

        drawGrid(grid);
        moves++;

        if (checkWin(grid, currentPlayer)) {
            if (currentPlayer == 'X') {
                printf("Congratulations %s! You have won!\n", human);
            } else {
                printf("Computer wins!\n");
            }
            break;
        }

        if (moves == 9) {
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

bool isMovesLeft(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                return true;  // There are still moves left
            }
        }
    }
    return false;  // No moves left
}

int evaluate(char grid[3][3]) {
    // Check rows for a win
    for (int row = 0; row < 3; row++) {
        if (grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2]) {
            if (grid[row][0] == 'O') return 10;   // Computer wins
            if (grid[row][0] == 'X') return -10;  // Human wins
        }
    }

    // Check columns for a win
    for (int col = 0; col < 3; col++) {
        if (grid[0][col] == grid[1][col] && grid[1][col] == grid[2][col]) {
            if (grid[0][col] == 'O') return 10;   // Computer wins
            if (grid[0][col] == 'X') return -10;  // Human wins
        }
    }

    // Check diagonals for a win
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        if (grid[0][0] == 'O') return 10;         // Computer wins
        if (grid[0][0] == 'X') return -10;        // Human wins
    }

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        if (grid[0][2] == 'O') return 10;         // Computer wins
        if (grid[0][2] == 'X') return -10;        // Human wins
    }

    // No one wins
    return 0;
}

int minimax(char grid[3][3], int depth, bool isMaximizing) {
    int score = evaluate(grid);

    if (score == 10)
        return score - depth;
    if (score == -10)
        return score + depth;

    if (!isMovesLeft(grid))
        return 0; //Draw

    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = 'O'; // Computer's move
                    best = fmax(best, minimax(grid, depth + 1, false));
                    grid[i][j] = ' '; // Undo move
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == ' ') {
                    grid[i][j] = 'X'; // Human's move
                    best = fmin(best, minimax(grid, depth + 1, true));
                    grid[i][j] = ' '; // Undo move
                }
            }
        }
        return best;
    }
}

void findBestMove(char grid[3][3], int *bestRow, int *bestCol) {
    int bestVal = INT_MIN;
    *bestRow = -1;
    *bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i][j] == ' ') {
                grid[i][j] = 'O';

                int moveVal = minimax(grid, 0, false);

                grid[i][j] = ' ';

                if (moveVal > bestVal) {
                    *bestRow = i;
                    *bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

void playHumanVsComputerDifficult(char grid[3][3], char *human) {
    char currentPlayer = 'X';
    int moves = 0;
    srand(time(0));

    while (1) {
        if (currentPlayer == 'X') {
            handlePlayerMove(grid, currentPlayer, human);
        } else {
            int bestRow, bestCol;
            findBestMove(grid, &bestRow, &bestCol);  // Determine the best move
            printf("Computer chooses: %d %d\n", bestRow, bestCol);
            grid[bestRow][bestCol] = 'O';  // Computer makes its move
        }

        drawGrid(grid);
        moves++;

        if (checkWin(grid, currentPlayer)) {
            if (currentPlayer == 'X') {
                printf("Congratulations %s! You have won!\n", human);
            } else {
                printf("Computer wins!\n");
            }
            break;
        }

        if (moves == 9) {
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void playHumanVsComputer(int difficulty){
    char grid[3][3];
    initializeGrid(grid);

    char human[20];
    printf("Player 1 (X), insert your Username:\n");
    scanf("%19s", human);

    if (difficulty == 0) {
        playHumanVsComputerEasy(grid, human);
    } else if (difficulty == 1) {
        playHumanVsComputerMedium(grid, human);
    } else {
        playHumanVsComputerDifficult(grid,human);
    }
    }

int main(void) {
        int mode = selectGameMode();

        if (mode == 1) {
            playHumanVsHuman();
        } else {
            int difficulty = selectDifficulty();
            playHumanVsComputer(difficulty);
        }

        return 0;
    }

