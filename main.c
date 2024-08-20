#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Player names for Human vs Human
void inputNames(char playerX[], char playerO[]) {
    printf("Player 1 (X), insert your Username:\n");
    scanf("%19s", playerX);
    printf("Player 2 (O), insert your Username:\n");
    scanf("%19s", playerO);
    printf("Welcome %s and %s\n", playerX, playerO);
}
//Draw the game's grid
void drawGrid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("[%c]", grid[i][j]);
        }
        printf("\n");
    }
}
//How do you want to play?
int gameMode() {
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

int checkWin(char grid[3][3], char currentPlayer) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((grid[i][0] == currentPlayer && grid[i][1] == currentPlayer && grid[i][2] == currentPlayer) ||
            (grid[0][i] == currentPlayer && grid[1][i] == currentPlayer && grid[2][i] == currentPlayer)) {
            return 1;
        }
    }
    // Check diagonals
    if ((grid[0][0] == currentPlayer && grid[1][1] == currentPlayer && grid[2][2] == currentPlayer) ||
        (grid[0][2] == currentPlayer && grid[1][1] == currentPlayer && grid[2][0] == currentPlayer)) {
        return 1;
    }
    return 0;
}

void startGameHVH(char playerX[], char playerO[]) {
    char grid[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    printf("%s (X) vs %s (O)\n", playerX, playerO);
    drawGrid(grid);

    int row, col;
    char currentPlayer = 'X';
    char *currentPlayerName = playerX;
    int moves = 0;

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
        drawGrid(grid);
        moves++;

        if (checkWin(grid, currentPlayer)) {
            printf("Congratulations %s! You have won!\n", currentPlayerName);
            break;
        }

        if (moves == 9) {
            printf("It's a draw!\n");
            break;
        }

        if (currentPlayer == 'X') {
            currentPlayer = 'O';
            currentPlayerName = playerO;
        } else {
            currentPlayer = 'X';
            currentPlayerName = playerX;
        }
    }
}

void hvh() {
    char playerX[20], playerO[20];
    inputNames(playerX, playerO);
    startGameHVH(playerX, playerO);
}

int selectDiff() {
    printf("Select a difficulty:\n");
    printf("A. Easy\nB. Medium\nC. Difficult\n");
    char level;
    scanf(" %c", &level);
    if (level == 'A') {
        return 0;
    } else if (level == 'B') {
        return 1;
    } else if (level == 'C') {
        return 2;
    } else {
        printf("Invalid Choice. Please pick between A, B, and C.\n");
    }
}

void easyMode() {
    char grid[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char human[20];
    printf("Enter your name: ");
    scanf("%19s", human);

    int row, col;
    char currentPlayer = 'X';
    int moves = 0;
    srand(time(0));

    while (1) {
        if (currentPlayer == 'X') {
            // Human's turn
            printf("%s, enter row and column (0-2): ", human);
            int result = scanf("%d %d", &row, &col);

            if (result != 2 || row < 0 || row > 2 || col < 0 || col > 2) {
                printf("Invalid move. Row and column must be between 0 and 2.\n");
                continue;
            }

            if (grid[row][col] != ' ') {
                printf("Cell already occupied. Try again.\n");
                continue;
            }

            grid[row][col] = 'X';
        } else {
            // Computer's turn (random move)
            do {
                row = rand() % 3;
                col = rand() % 3;
            } while (grid[row][col] != ' ');

            printf("Computer chooses: %d %d\n", row, col);
            grid[row][col] = 'O';
        }

        drawGrid(grid);
        moves++;

        // Check if the current player won
        if (checkWin(grid, currentPlayer)) {
            if (currentPlayer == 'X') {
                printf("Congratulations %s! You have won!\n", human);
            } else {
                printf("Computer wins!\n");
            }
            break;
        }

        // Check for a draw
        if (moves == 9) {
            printf("It's a draw!\n");
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void hvc() {
    int difficulty = selectDiff();
    if (difficulty == 0) {
        easyMode();
    }
}

void startGameHVC(int difficulty) {
    char grid[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    printf("Enter your name: ");
    char human[20];
    scanf("%19s", human);
    printf("%s (X) vs Computer (O)\n", human);
    drawGrid(grid);

    difficulty=selectDiff;
    if (difficulty == 0) {
        easyMode(human);
    }
}

int main(void) {
    int mode = gameMode();
    if (mode == 1) {
        hvh();
    } else {
        hvc();
        //const int difficulty = selectDiff();
        //if(difficulty==0){
        //easyMode()};
        //startGameHVC(difficulty);
    }

    return 0;
}
