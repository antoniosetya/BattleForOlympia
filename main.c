#include "libs/boolean.h"
#include "libs/unit.h"
#include "libs/player.h"
#include "libs/UnitList.h"
#include "libs/VilList.h"
#include "libs/map.h"
#include "libs/queue.h"
#include "libs/stackt.h"
#include "attack.c"
#include <stdio.h>

Player P_Data[3]; /* Redeclaring global extern variable from player.h */
Queue P_Turns;
Stack Mov_Data;
MAP Map_Data;
int CurrPlayer;
VilList FreeVillage;

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

void SaveGame() {
  char filename[128];
  printf("Insert file name (max. 128 characters, including .txt) : ");
  int i = 0;
  char temp = getchar();
  while ((temp == '\n') || (temp == ' ')) { /* "Eats" any previous whitespace */
    temp = getchar();
  }
  while ((temp != '\n') && i < 127) {
    filename[i] = temp;
    i++;
    temp = getchar();
  }
  filename[i] = '\0';
  FILE *fs = fopen(filename,"w");
  fprintf(fs,"CurrentPlayer : %d\n",CurrPlayer);
  for (i = 1;i <= 2;i++) {
    fprintf(fs,"<Player %d>\n",i);
    fprintf(fs,"Gold : %d\n",Gold(P_Data[i]));
    fprintf(fs,"<UNITS>\n");
    if (!UL_IsEmpty(Units(P_Data[i]))) {
      ul_address Pt = UL_First(Units(P_Data[i]));
      while (Pt != Nil) {
        fprintf(fs,"%c | %d | %d | %d | %c |",UnitType(UL_Info(Pt)),MaxHP(UL_Info(Pt)),HP( UL_Info(Pt)),Attack( UL_Info(Pt)),AttackType( UL_Info(Pt)));
        fprintf(fs,"%d | %d | %d | %d %d | %d | %.2f\n",MaxSteps( UL_Info(Pt)),Steps( UL_Info(Pt)),AtkState( UL_Info(Pt)),Absis(Loc( UL_Info(Pt))),Ordinat(Loc( UL_Info(Pt))),Owner( UL_Info(Pt)),AtkProb( UL_Info(Pt)));
        Pt = UL_Next(Pt);
      }
    }
    fprintf(fs,"</UNITS>\n");
    fprintf(fs,"<VILLAGES>\n");
    if (!VL_IsEmpty(Villages(P_Data[i]))) {
      vl_address PtVL = VL_First(Villages(P_Data[i]));
      while (PtVL != Nil) {
        fprintf(fs,"%d %d\n",Absis(VL_Info(PtVL).pos),Ordinat(VL_Info(PtVL).pos));
        PtVL = VL_Next(PtVL);
      }
    }
    fprintf(fs,"</VILLAGES>\n");
    fprintf(fs,"Income : %d\n",Income(P_Data[i]));
    fprintf(fs,"Upkeep : %d\n",Upkeep(P_Data[i]));
    fprintf(fs,"Base : %d %d\n",Absis(Base(P_Data[i])),Ordinat(Base(P_Data[i])));
    fprintf(fs,"</PLAYER %d>\n",i);
  }
  fclose(fs);
  printf("Done writing to %s.\n",filename);
}

int ProcessGameCommand(char *in) {
  int val;
  if ((in[0] == 'M') && (in[1] == 'O') && (in[2] == 'V') && (in[3] == 'E') && (in[4] == '\0')) {
    val = 1;
  }
  else if ((in[0] == 'M') && (in[1] == 'A') && (in[2] == 'P') && (in[3] == '\0')) {
    val = 6;
  }
  else if ((in[0] == 'U') && (in[1] == 'N') && (in[2] == 'D') && (in[3] == 'O') && (in[4] == '\0')) {
    val = 2;
  }
  else if ((in[0] == 'C') && (in[1] == 'H') && (in[2] == 'A') && (in[3] == 'N') && (in[4] == 'G') && (in[5] == 'E') && (in[6] == '_') && (in[7] == 'U') && (in[8] == 'N') && (in[9] == 'I') && (in[10] == 'T') && (in[11] == '\0')) {
    val = 3;
  }
  else if ((in[0] == 'R') && (in[1] == 'E') && (in[2] == 'C') && (in[3] == 'R') && (in[4] == 'U') && (in[5] == 'I') && (in[6] == 'T') && (in[7] == '\0')) {
    val = 4;
  }
  else if ((in[0] == 'A') && (in[1] == 'T') && (in[2] == 'T') && (in[3] == 'A') && (in[4] == 'C') && (in[5] == 'K') && (in[6] == '\0')) {
    val = 5;
  }
  else if ((in[0] == 'I') && (in[1] == 'N') && (in[2] == 'F') && (in[3] == 'O') && (in[4] == '\0')) {
    val = 7;
  }
  else if ((in[0] == 'E') && (in[1] == 'N') && (in[2] == 'D') && (in[3] == '_') && (in[4] == 'T') && (in[5] == 'U') && (in[6] == 'R') && (in[7] == 'N') && (in[8] == '\0')) {
    val = 8;
  }
  else if ((in[0] == 'E') && (in[1] == 'X') && (in[2] == 'I') && (in[3] == 'T') && (in[4] == '\0')) {
      val = 10;
  }
  else if ((in[0] == 'S') && (in[1] == 'A') && (in[2] == 'V') && (in[3] == 'E') && (in[4] == '\0')) {
      val = 9;
  }
  else {
    val = -999;
  }
  return val;
}

void StartGame() {
  printf("Game will now starting...\n");
  boolean Exit = false;
  char command[15];
  do {
    Del(&P_Turns,&CurrPlayer); /* Gets whose turn is this */
    Add(&P_Turns,CurrPlayer); /* Push back to the queue */
    printf("It's player %d's turn!\n",CurrPlayer);
    boolean EndTurn = false;
    do {
      int i = 0;
      printf("What do you want to do? : ");
      char temp = getchar();
      while ((temp == '\n') || (temp == ' ')) { /* "Eats" any previous whitespace */
        temp = getchar();
      }
      while ((temp != '\n') && i < 14) {
        command[i] = temp;
        i++;
        temp = getchar();
      }
      command[i] = '\0';
      switch (ProcessGameCommand(command)) {
        case 1:
          printf("Move\n");
          break;
        case 2:
          printf("Undo\n");
          break;
        case 3:
          printf("Change_Unit\n");
          break;
        case 4:
          printf("Recruit\n");
          break;
        case 5:
          if(AtkState(Info(UL_Curr(Units(P_Data[CurrPlayer]))==false))){
		printf("This unit cannot Attack\n");
	   } 
		 else{
		    if(CurrPlayer==1){
			    attack(&Units(P_Data[CurrPlayer]),&Units(P_Data[2]));
			}
			else{
			    attack(&Units(P_Data[CurrPlayer]),&Units(P_Data[1]));
			}
		 }
          break;
        case 6:
          DrawMAP(Map_Data);
          break;
        case 7:
          printf("Info\n");
          break;
        case 8:
          printf("End_Turn\n");
          break;
        case 9:
          SaveGame();
          break;
        case 10:
          Exit = true;
          break;
        default:
          printf("Wrong command!\n");
      }
    }
    while (!EndTurn && !Exit);
  }
  while (!Exit);
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
    VL_CreateEmpty(&FreeVillage);
    Add(&P_Turns,1);
    Add(&P_Turns,2);
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
    /* Randomize the position of each player's base.
       Rules : Cannot be on the map's edge for rows, between col 2 - 3. */
    int minrow = 2;
    int rowrange = row - minrow - 1;
    float random = randomFloat();
    random = randomFloat(); /* Re-run the randomizer, because the first one always generate 0 */
    float threshold = 0.5;
    if (random >= threshold) {
      Absis(Base(P_Data[1])) = 3;
      Absis(Base(P_Data[2])) = col - 2;
    }
    else {
      Absis(Base(P_Data[1])) = 2;
      Absis(Base(P_Data[2])) = col - 3;
    }
    int i = 0;
    boolean Passed = false;
    threshold = 0.95;
    while ((i <= rowrange) && !Passed) {
      random = randomFloat();
      if (random >= threshold) {
        Passed = true;
      }
      else {
        i++;
        threshold-=0.1;
      }
    }
    if (i > rowrange) {
      Ordinat(Base(P_Data[1])) = minrow + rowrange;
      Ordinat(Base(P_Data[2])) = row - rowrange - 1;
    }
    else {
      Ordinat(Base(P_Data[1])) = minrow + i;
      Ordinat(Base(P_Data[2])) = row - i -1;
    }
    /* Updates the map */
    POINT tempC;
    UpdateBuildingOnMap(&Map_Data,Base(P_Data[1]),'T',1);
    tempC = MakePOINT(Absis(Base(P_Data[1])),Ordinat(Base(P_Data[1])));
    Ordinat(tempC)--;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
    Absis(tempC)++; Ordinat(tempC)++;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
    Absis(tempC)--; Ordinat(tempC)++;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
    Absis(tempC)--; Ordinat(tempC)--;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
    UpdateBuildingOnMap(&Map_Data,Base(P_Data[2]),'T',2);
    tempC = MakePOINT(Absis(Base(P_Data[2])),Ordinat(Base(P_Data[2])));
    Ordinat(tempC)--;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
    Absis(tempC)++; Ordinat(tempC)++;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
    Absis(tempC)--; Ordinat(tempC)++;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
    Absis(tempC)--; Ordinat(tempC)--;
    UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
    /* Randomize the occurence of a village */
    int NVil = (row * col) / 12;
    int j;
    threshold = 0.93;
    POINT temp;
    B_Data tempVil;
    do {
      for (i = 1;(i <= row) && (NVil > 0);i++) {
        for (j = 1;(j <= col) && (NVil > 0);j++) {
          random = randomFloat();
          if ((random > threshold) && (Elmt(Map_Data,j,i).BData.Type == 'N')) {
            temp = MakePOINT(j,i);
            tempVil.Type = 'V';
            tempVil.owner = 0;
            tempVil.pos = temp;
            VL_InsVFirst(&FreeVillage,tempVil);
            NVil--;
          }
        }
      }
    }
    while(NVil > 0);
    /* Updates the map */
    vl_address Pt = VL_First(FreeVillage);
    while (Pt != Nil) {
      UpdateBuildingOnMap(&Map_Data,VL_Info(Pt).pos,VL_Info(Pt).Type,VL_Info(Pt).owner);
      Pt = VL_Next(Pt);
    }
    StartGame();
  }
  else {
    // Loads a file
  }
}

int main() {
    int execode;
    do {
      execode = main_menu();
      if (execode == 1) {
        initialize_game(true,Nil);
      }
      else if (execode == 2) {
        //load_game()
        //initialize_game(false,<pointer to char[] that contains the filename>);
        //start_game()
        //blablabla
        printf("LOAD GAME\n");
      }
    }
    while (execode != 3);
    /* execode == 3 */
    printf("Program exiting. Until next time, then...!\n");
}
