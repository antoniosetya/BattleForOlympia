#include "libs/boolean.h"
#include "libs/unit.h"
#include "libs/player.h"
#include "libs/mesinkata.h"
#include "libs/UnitList.h"
#include "libs/VilList.h"
#include "libs/map.h"
#include "libs/queue.h"
#include "libs/stackt.h"
#include "attack.c"
#include "info.c"
#include "change_unit.c"
#include <stdio.h>

// Redeclaring global extern variable from mesinkata.h
boolean EndKata;
Kata CKata;
// Redeclaring global extern variable from player.h
Player P_Data[3];
UTemplate TemplateUnit[4]; // Contains template units
Queue P_Turns; // Stores turns of the player
Stack Mov_Data; // Stores movement data of a unit
MAP Map_Data; // Stores map data
int CurrPlayer; // Stores which player are playing right now
VilList FreeVillage; // Lists all available/empty villages

int main_menu() {
/*  Shows the main menu of the program when the program starts for the first time
    Main menu appearance is subject to change
    Returns these codes :
    1 : Start new game
    2 : Loads a previously saved game
    3 : Exit the program */
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

int ProcessGameCommand(Kata in) {
  int val = 1;
  Kata tempKey[11];
  CreateKata(&tempKey[1],"MOVE");
  CreateKata(&tempKey[2],"UNDO");
  CreateKata(&tempKey[3],"CHANGE_UNIT");
  CreateKata(&tempKey[4],"RECRUIT");
  CreateKata(&tempKey[5],"ATTACK");
  CreateKata(&tempKey[6],"MAP");
  CreateKata(&tempKey[7],"INFO");
  CreateKata(&tempKey[8],"END_TURN");
  CreateKata(&tempKey[9],"SAVE");
  CreateKata(&tempKey[10],"EXIT");
  boolean found = false;
  while ((val < 11) && !found) {
    found = IsKataSama(in,tempKey[val]);
    if (!found) val++;
  }
  if (!found) val = -999;
  return val;
}

/*
void Recruit() {
	if (UnitType(UL_Info(UL_Curr(Units(P_Data[CurrPlayer])))) != 'K') {
		printf("Only King(s) can recruit!\n");
	}
	else {
		POINT castle_p;
		printf("Enter coordinate of empty castle: ");
		BacaPOINT(&castle_p);
		if (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type != 'C')
			printf("There is no castle here!\n");
		else {
			if (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit != Nil)
				printf("That castle is occupied!\n");
			else {
				int unit_type;
				printf("=== List of Recruits ===\n");
				printf("1. Archer | Health 20 | ATK 4 | DEF 1 | 5G\n");
				printf("2. Swordsman | Health 20 | ATK 3 | DEF 2 | 4G\n");
				printf("Enter no. of unit you want to recruit: ");
				scanf("%d",&unit_type);

				while (unit_type < 1 || unit_type > 2) {
					printf("Input invalid, try again\n");
					scanf("%d",&unit_type);
				}

				if (unit_type == 1) {
					if (Gold(P_Data[CurrPlayer]) < 5)
						printf("Not enough money\n");
					else {
						Gold(P_Data[CurrPlayer]) -= 5;
						printf("You have recruited an archer!\n");
					}
				}
				else if (unit_type == 2) {
					if (Gold(P_Data[CurrPlayer]) < 4)
						printf("Not enough money\n");
					else
						Gold(P_Data[CurrPlayer]) -= 4;
						printf("You have recruited a swordsman!\n");
				}
			}
		}
	}
}
*/

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
      Kata input;
      BacaKata(&input);
      switch (ProcessGameCommand(input)) {
        case 1:
          printf("Move\n");
          break;
        case 2:
          printf("Undo\n");
          break;
        case 3:
          ChangeUnit(CurrPlayer,&UL_Curr(Units(P_Data[CurrPlayer])));
          break;
        case 4:
          printf("Recruit\n");
          break;
        case 5:
          if(AtkState(UL_Info(UL_Curr(Units(P_Data[CurrPlayer])))) == false ){
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
          DrawMAP(Map_Data,CurrPlayer);
          break;
        case 7:
          printf("Info\n");
          InfoCmd(Map_Data);
          break;
        case 8:
          printf("End_Turn\n");
          //EndTurn = true;
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
    // Initialize players
    InitPlayer(&P_Data[1],1);
    InitPlayer(&P_Data[2],2);
    // Initialize stack and queue
    CreateEmptyStack(&Mov_Data);
    CreateEmptyQueue(&P_Turns);
    // Initialize free village list
    VL_CreateEmpty(&FreeVillage);
    // Adds the player to the queue
    Add(&P_Turns,1);
    Add(&P_Turns,2);
    // Asks the user about the size of the map
    int row, col;
    boolean isValid;
    do {
      printf("Input the map size (rows cols, separated by a space) : ");
      scanf("%d %d",&row,&col);
      isValid = (row >= 8) && (col >= 8);
      if (!isValid) printf("Map dimension is not valid! (minimum is 8x8)\n");
    }
    while (!isValid);
    // Initialize map
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
    /* Generate "kings" for each player, auto-select it, and updates the map */
    Unit tempKing;
    InitUnit(&tempKing,TemplateUnit[0],1,Base(P_Data[1]));
    UL_InsVFirst(&Units(P_Data[1]),tempKing);
    UL_Curr(Units(P_Data[1])) = UL_First(Units(P_Data[1]));
    UpdateUnitOnMap(&Map_Data,Base(P_Data[1]),&UL_Info(UL_First(Units(P_Data[1]))));
    InitUnit(&tempKing,TemplateUnit[0],2,Base(P_Data[2]));
    UL_InsVFirst(&Units(P_Data[2]),tempKing);
    UL_Curr(Units(P_Data[2])) = UL_First(Units(P_Data[2]));
    UpdateUnitOnMap(&Map_Data,Base(P_Data[2]),&UL_Info(UL_First(Units(P_Data[2]))));
    /* Starts the game */
    StartGame();
  }
  else {
    // Loads a file
  }
}

void LoadUnitSpecs() {
/* Loads the unit "templates" into TemplateUnit */
  STARTKATA("unitstats.txt");
  /* Keywords
  Kata Keywords[8];
  CreateKata(&Keywords[0],"<K>");
  CreateKata(&Keywords[1],"</K>");
  CreateKata(&Keywords[2],"<A>");
  CreateKata(&Keywords[3],"</A>");
  CreateKata(&Keywords[4],"<S>");
  CreateKata(&Keywords[5],"</S>");
  CreateKata(&Keywords[6],"<W>");
  CreateKata(&Keywords[7],"</W>");
  CreateKata(&Keywords[8],"M");
  CreateKata(&Keywords[9],"R");
  boolean FileValid = true;  */
  int i = 0;
  while (!EndKata) {
    TemplateType(TemplateUnit[i]) = CKata.TabKata[2];
    ADVKATA();
    TemplateAtkType(TemplateUnit[i]) = CKata.TabKata[1];
    ADVKATA();
    TemplateHP(TemplateUnit[i]) = KataToInteger(CKata);
    ADVKATA();
    TemplateAtk(TemplateUnit[i]) = KataToInteger(CKata);
    ADVKATA();
    TemplateSteps(TemplateUnit[i]) = KataToInteger(CKata);
    ADVKATA();
    Price(TemplateUnit[i]) = KataToInteger(CKata);
    ADVKATA();
    UpkeepCost(TemplateUnit[i]) = KataToInteger(CKata);
    ADVKATA();
    ADVKATA();
    i++;
  }
}

int main() {
    int execode;
    LoadUnitSpecs();
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
