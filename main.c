#include <stdio.h>

#define SIZE 3

void inputName() {
    char username[20];
    printf("Insert your Username:\n");
    scanf("%19s", username);
    printf("Welcome %s\n", username);
}

void drawGrid(char grid[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            printf("[%c]", grid[i][j]);
        printf("\n");
    }
}

void difficulty() {

}

int gameMode() {
    char gameModeChoice;
    printf("Select a Game Mode:\n");
    printf("A. Human VS Computer \n");
    printf("B. Human vs Human \n");
    printf("Insert A or B");
    scanf("%c", &gameModeChoice);
    if(gameModeChoice!='A' && gameModeChoice !='B') {
        printf("Invalid Choice. Please pick between A and B");
    }else if (gameModeChoice =='A') {
        return 0;
    }else {
        return 1;
    }

    return 0;
}

void userSelect() {
    char userChoice;
    printf("Pick One: X or O\n");
    scanf("%c", &userChoice);
    if(userChoice!= 'X' && userChoice!= 'O') {
        printf("Invalid Choice. Please pick between X and O!");
    }
}

void startGame() {

}

int main(void) {
    char grid[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    inputName();
    drawGrid(grid);
    return 0;
}
