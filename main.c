#include <stdio.h>

void inputNames(char playerX[], char playerO[]) {
    printf("Player 1 (X), insert your Username:\n");
    scanf("%19s", playerX);
    printf("Player 2 (O), insert your Username:\n");
    scanf("%19s", playerO);
    printf("Welcome %s and %s\n", playerX, playerO);
}

void drawGrid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("[%c]", grid[i][j]);
        }
        printf("\n");
    }
}

int gameMode() {
    char gameModeChoice;
    while (1) {
        printf("Select a Game Mode:\n");
        printf("A. Human VS Computer \n");
        printf("B. Human vs Human \n");
        printf("Insert A or B: ");
        scanf(" %c", &gameModeChoice);
        if (gameModeChoice != 'A' && gameModeChoice != 'B') {
            printf("Invalid Choice. Please pick between A and B\n");
        } else if (gameModeChoice == 'A') {
            return 0;
        } else {
            return 1;
        }
    }
}

int checkWin(char grid[3][3], char currentPlayer) {
    for(int i=0; i<3; i++) {
        if ( (grid[i][0] == currentPlayer && grid[i][1] == currentPlayer && grid[i][2] == currentPlayer) ||
             (grid[0][i] == currentPlayer && grid[1][i] == currentPlayer && grid[2][i] == currentPlayer)) {
            return 1;
             }
    }
        if ((grid[0][0] == currentPlayer && grid[1][1] == currentPlayer && grid[2][2] == currentPlayer) ||
            (grid[0][2] == currentPlayer && grid[1][1] == currentPlayer && grid[2][0] == currentPlayer)) {
            return 1;
            }
    return 0;
    }

void startGame(char playerX[], char playerO[]) {
    char grid[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    printf("%s (X) vs %s (O)\n", playerX, playerO);
    drawGrid(grid);

    int row,col;
    char currentPlayer ='X';
    char *currentPlayerName = playerX;
    int moves = 0;

    while (1) {
        int result = scanf("%d %d", &row, &col);
        while (getchar() != '\n')
        if (result != 2 || row < 0 || row > 2 || col < 0 || col > 2 || grid[row][col] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }
            grid[row][col]=currentPlayer;
            drawGrid(grid);
            moves++;

            if (checkWin(grid, currentPlayer)) {
                printf("Congratulations %s! You have won!\n", currentPlayerName);
                break;
            }
            if(moves==9) {
                printf("It's a draw!");
            }

            if(currentPlayer=='X') {
                currentPlayer = 'O';
                currentPlayerName=playerO;
            }else {
                currentPlayer='X';
                currentPlayerName=playerX;
            }

    }
}

void hvh() {
    char playerX[20], playerO[20];
    inputNames(playerX, playerO);
    startGame(playerX, playerO);
}

int main(void) {
    int mode = gameMode();
    if (mode == 1) {
        hvh();
    } else {
        // Human Vs Computer Goes Here
        printf("Human vs Computer mode update is coming soon!.\n");
    }

    return 0;
}
