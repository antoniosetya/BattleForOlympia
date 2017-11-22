#include "libs/boolean.h"
#include "libs/unit.h"
#include "libs/player.h"
#include "libs/UnitList.h"
#include "libs/VilList.h"
#include "libs/map.h"
#include "libs/queue.h"
#include "libs/stackt.h"
#include <stdio.h>

Player P_Data[3]; /* Redeclaring global extern variable from player.h */
Queue P_Turns;
Stack Mov_Data;
MAP Map_Data;

int main_menu() {
/*  Shows the main menu of the program when the program starts for the first time
    Main menu appearance is subject to change
    Returns these codes :
    1 : Start new game
    2 : Loads a previously saved game
    3 : Exit the program
*/
    int com;
    printf("\n======================================================================================\n");
    printf("  ____        _   _   _         __              ____  _                       _       \n");
    printf(" |  _ \\      | | | | | |       / _|            / __ \\| |                     (_)      \n");
    printf(" | |_) | __ _| |_| |_| | ___  | |_ ___  _ __  | |  | | |_   _ _ __ ___  _ __  _  __ _ \n");
    printf(" |  _ < / _` | __| __| |/ _ \\ |  _/ _ \\| '__| | |  | | | | | | '_ ` _ \\| '_ \\| |/ _` |\n");
    printf(" | |_) | (_| | |_| |_| |  __/ | || (_) | |    | |__| | | |_| | | | | | | |_) | | (_| |\n");
    printf(" |____/ \\__,_|\\__|\\__|_|\\___| |_| \\___/|_|     \\____/|_|\\__, |_| |_| |_| .__/|_|\\__,_|\n");
    printf("                                                         __/ |         | |            \n");
    printf("                                                        |___/          |_|            \n");
    printf("======================================================================================\n\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");
    printf("--------------------------------------------------------------------------------------\n");
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

void initialize_game(boolean NewGame,char *SaveFile) {
  /* If NewGame = False -> Reads the file from *SaveFile, then initialize anything else needed
     If NewGame = True -> Initializes players, buildings, and load unit datas
                          *SaveFile can be anything, recommended to pass null pointer */
  if (NewGame) {
    InitPlayer(&P_Data[1],1);
    InitPlayer(&P_Data[2],2);
    CreateEmptyStack(&Mov_Data);
    CreateEmptyQueue(&P_Turns);
    int row, col;
    boolean isValid;
    do {
      printf("Input the map size (rows cols, separated by a space) : ");
      scanf("%d %d",&row,&col);
      isValid = (row >= 8) && (col >= 8);
      if (!isValid) printf("Map dimension is not valid! (minimum is 8x8)\n");
    }
    while (!isValid);
    InitMAP(row,col,&Map_Data);

  }
  else {

  }
}

int main() {
    int execode = main_menu();
    if (execode == 1) {
        //initialize_game(true,Nil);
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
