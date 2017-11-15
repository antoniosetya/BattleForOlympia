#include "libs/boolean.h"
#include <stdio.h>

int main_menu() {
/*  Shows the main menu of the program when the program starts for the first time
    Main menu appearance is subject to change
    Returns these codes :
    1 : Start new game
    2 : Loads a previously saved game
    3 : Exit the program
*/
    int com;
    printf("WOAH, MAIN MENU HERE!\n");
    printf("=============================\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");
    printf("-----------------------------\n");
    boolean valid = false;
    do {
        printf("Your command? (insert the menu number) : ");
        scanf("%d",&com);
        valid = ((com >= 1) && (com <= 3));
        if (!valid) printf("Input is not valid!\n");
    }
    while (!valid);
    return com;
}

int main() {
    int execode = main_menu();
    if (execode == 1) {
        //initialize_game()
        //start_game()
        //blablabla
        printf("START GAME\n");
    }
    else if (execode == 2) {
        //load_game()
        //initialize_game()
        //start_game()
        //blablabla
        printf("LOAD GAME\n");
    }
    /* execode == 3 */
    printf("Program exiting...\n");
}