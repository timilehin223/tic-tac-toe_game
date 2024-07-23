#include <stdio.h>

int main(void) {
    char username[20];
    printf("Insert your Username:\n");
    scanf("%19s", username);
    printf("Welcome %s", username);
    return 0;
}
