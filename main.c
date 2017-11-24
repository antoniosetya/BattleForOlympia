#include "libs/boolean.h"
#include "libs/pcolor.h"
#include "libs/unit.h"
#include "libs/player.h"
#include "libs/buildings.h"
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
  Kata filename;
  printf("Enter the filename (max. 100 characters) : ");
  BacaKata(&filename);
  FILE *fs = fopen(filename.TabKata+1,"w");
  fprintf(fs,"CurrentPlayer : %d\n",CurrPlayer);
  fprintf(fs,"MapSize : %d %d\n",NBrs(Map_Data),NKol(Map_Data));
  fprintf(fs,"<FREEVILLAGE>\n");
  vl_address PtFVL = VL_First(FreeVillage);
  while (PtFVL != Nil) {
    fprintf(fs,"%d %d\n",Absis(BuildPos(VL_Info(PtFVL))),Ordinat(BuildPos(VL_Info(PtFVL))));
    PtFVL = VL_Next(PtFVL);
  }
  fprintf(fs,"</FREEVILLAGE>\n");
  int i;
  for (i = 1;i <= 2;i++) {
    fprintf(fs,"<PLAYER%d>\n",i);
    fprintf(fs,"Gold : %d\n",Gold(P_Data[i]));
    fprintf(fs,"<UNITS>\n");
    if (!UL_IsEmpty(Units(P_Data[i]))) {
      ul_address Pt = UL_First(Units(P_Data[i]));
      while (Pt != Nil) {
        fprintf(fs,"%c | %d | %d | %d | %c | ",UnitType(UL_Info(Pt)),MaxHP(UL_Info(Pt)),HP( UL_Info(Pt)),Attack( UL_Info(Pt)),AttackType( UL_Info(Pt)));
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
    fprintf(fs,"</PLAYER%d>\n",i);
  }
  fprintf(fs,"*");
  fclose(fs);
  printf("Done writing to ");TulisKata(filename);printf("\n");
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
    printf("%sIt's player %d's turn!%s\n",Color(P_Data[CurrPlayer]),CurrPlayer,NORMAL);
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
  // Initialize players
  InitPlayer(&P_Data[1],1);
  InitPlayer(&P_Data[2],2);
  // Initialize stack and queue
  CreateEmptyStack(&Mov_Data);
  CreateEmptyQueue(&P_Turns);
  // Initialize free village list
  VL_CreateEmpty(&FreeVillage);
  if (NewGame) {
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
  }
  else {
    printf("Reading from %s...\n",SaveFile);
    STARTKATA(SaveFile); // starts reading the file
    Kata keyword[16];
    int row, col;
    CreateKata(&keyword[0],"CurrentPlayer");
    CreateKata(&keyword[1],"MapSize");
    CreateKata(&keyword[2],"<FREEVILLAGE>");
    CreateKata(&keyword[3],"</FREEVILLAGE>");
    CreateKata(&keyword[4],"<PLAYER1>");
    CreateKata(&keyword[5],"</PLAYER1>");
    CreateKata(&keyword[6],"<PLAYER2>");
    CreateKata(&keyword[7],"</PLAYER2>");
    CreateKata(&keyword[8],"Gold");
    CreateKata(&keyword[9],"<UNITS>");
    CreateKata(&keyword[10],"</UNITS>");
    CreateKata(&keyword[11],"<VILLAGES>");
    CreateKata(&keyword[12],"</VILLAGES>");
    CreateKata(&keyword[13],"Income");
    CreateKata(&keyword[14],"Upkeep");
    CreateKata(&keyword[15],"Base");
    while (!EndKata) {
      if (IsKataSama(CKata,keyword[0])) {
        printf("Reading player turns...\n");
        ADVKATA();
        ADVKATA();
        CurrPlayer = KataToInteger(CKata);
        Add(&P_Turns,CurrPlayer);
        if (CurrPlayer == 1) {
          Add(&P_Turns,2);
        }
        else {
          Add(&P_Turns,1);
        }
      }
      else if (IsKataSama(CKata,keyword[1])) {
        printf("Reading map...\n");
        ADVKATA();
        ADVKATA();
        row = KataToInteger(CKata);
        ADVKATA();
        col = KataToInteger(CKata);
        InitMAP(row,col,&Map_Data);
      }
      else if (IsKataSama(CKata,keyword[2])) {
        printf("Reading building data...\n");
        VL_CreateEmpty(&FreeVillage);
        ADVKATA();
        B_Data temp;
        BuildType(temp) = 'V';
        BuildOwner(temp) = 0;
        while (!IsKataSama(CKata,keyword[3])) {
          col = KataToInteger(CKata);
          ADVKATA();
          row = KataToInteger(CKata);
          BuildPos(temp) = MakePOINT(col,row);
          VL_InsVFirst(&FreeVillage,temp);
          UpdateBuildingOnMap(&Map_Data,BuildPos(temp),BuildType(temp),BuildOwner(temp));
          ADVKATA();
        }
      }
      else if (IsKataSama(CKata,keyword[4])) {
        printf("Reading player 1 data...\n");
        InitPlayer(&P_Data[1],1);
        ADVKATA();
        while (!IsKataSama(CKata,keyword[5])) {
          if (IsKataSama(CKata,keyword[8])){
            printf("Setting player 1 gold...\n");
            ADVKATA();
            ADVKATA();
            Gold(P_Data[1]) = KataToInteger(CKata);
          }
          else if (IsKataSama(CKata,keyword[9])) {
            printf("Reading player 1 units...\n");
            UL_CreateEmpty(&Units(P_Data[1]));
            ADVKATA();
            Unit temp;
            while (!IsKataSama(CKata,keyword[10])) {
              UnitType(temp) = CKata.TabKata[1];
              ADVKATA();
              ADVKATA();
              MaxHP(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              HP(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Attack(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              AttackType(temp) = CKata.TabKata[1];
              ADVKATA();
              ADVKATA();
              MaxSteps(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Steps(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              AtkState(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Absis(Loc(temp)) = KataToInteger(CKata);
              ADVKATA();
              Ordinat(Loc(temp)) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Owner(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              AtkProb(temp) = atof(CKata.TabKata+1);
              ul_address ul_temp = UL_Alokasi(temp);
              UL_InsertLast(&Units(P_Data[1]),ul_temp);
              UpdateUnitOnMap(&Map_Data,Loc(UL_Info(ul_temp)),&UL_Info(ul_temp));
              ADVKATA();
            }
            UL_Curr(Units(P_Data[1])) = UL_First(Units(P_Data[1]));
          }
          else if (IsKataSama(CKata,keyword[11])) {
            B_Data temp;
            BuildType(temp) = 'V';
            BuildOwner(temp) = 1;
            VL_CreateEmpty(&Villages(P_Data[1]));
            ADVKATA();
            printf("Reading player 1 villages...\n");
            while (!IsKataSama(CKata,keyword[12])) {
              row = KataToInteger(CKata);
              ADVKATA();
              col = KataToInteger(CKata);
              BuildPos(temp) = MakePOINT(col,row);
              VL_InsVLast(&Villages(P_Data[1]),temp);
              UpdateBuildingOnMap(&Map_Data,BuildPos(temp),BuildType(temp),BuildOwner(temp));
              ADVKATA();
            }
          }
          else if (IsKataSama(CKata,keyword[13])) {
            ADVKATA();
            ADVKATA();
            Income(P_Data[1]) = KataToInteger(CKata);
          }
          else if (IsKataSama(CKata,keyword[14])) {
            ADVKATA();
            ADVKATA();
            Upkeep(P_Data[1]) = KataToInteger(CKata);
          }
          else if (IsKataSama(CKata,keyword[15])) {
            printf("Setting player 1 base...\n");
            ADVKATA();
            ADVKATA();
            col = KataToInteger(CKata);
            ADVKATA();
            row = KataToInteger(CKata);
            Base(P_Data[1]) = MakePOINT(col,row);
            UpdateBuildingOnMap(&Map_Data,Base(P_Data[1]),'T',1);
            POINT tempC = Base(P_Data[1]);
            Ordinat(tempC)--;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
            Absis(tempC)++; Ordinat(tempC)++;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
            Absis(tempC)--; Ordinat(tempC)++;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
            Absis(tempC)--; Ordinat(tempC)--;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',1);
          }
          ADVKATA();
        }
      }
      else if (IsKataSama(CKata,keyword[6])) {
        printf("Reading player 2 data...\n");
        InitPlayer(&P_Data[2],2);
        ADVKATA();
        while (!IsKataSama(CKata,keyword[7])) {
          if (IsKataSama(CKata,keyword[8])){
            ADVKATA();
            ADVKATA();
            Gold(P_Data[2]) = KataToInteger(CKata);
          }
          else if (IsKataSama(CKata,keyword[9])) {
            UL_CreateEmpty(&Units(P_Data[2]));
            ADVKATA();
            Unit temp;
            while (!IsKataSama(CKata,keyword[10])) {
              UnitType(temp) = CKata.TabKata[1];
              ADVKATA();
              ADVKATA();
              MaxHP(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              HP(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Attack(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              AttackType(temp) = CKata.TabKata[1];
              ADVKATA();
              ADVKATA();
              MaxSteps(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Steps(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              AtkState(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Absis(Loc(temp)) = KataToInteger(CKata);
              ADVKATA();
              Ordinat(Loc(temp)) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              Owner(temp) = KataToInteger(CKata);
              ADVKATA();
              ADVKATA();
              AtkProb(temp) = atof(CKata.TabKata+1);
              ul_address ul_temp = UL_Alokasi(temp);
              UL_InsertLast(&Units(P_Data[2]),ul_temp);
              UpdateUnitOnMap(&Map_Data,Loc(temp),&UL_Info(ul_temp));
              ADVKATA();
            }
            UL_Curr(Units(P_Data[2])) = UL_First(Units(P_Data[2]));
          }
          else if (IsKataSama(CKata,keyword[11])) {
            B_Data temp;
            BuildType(temp) = 'V';
            BuildOwner(temp) = 2;
            VL_CreateEmpty(&Villages(P_Data[2]));
            ADVKATA();
            while (!IsKataSama(CKata,keyword[12])) {
              row = KataToInteger(CKata);
              ADVKATA();
              col = KataToInteger(CKata);
              BuildPos(temp) = MakePOINT(col,row);
              VL_InsVLast(&Villages(P_Data[2]),temp);
              UpdateBuildingOnMap(&Map_Data,BuildPos(temp),BuildType(temp),BuildOwner(temp));
              ADVKATA();
            }
          }
          else if (IsKataSama(CKata,keyword[13])) {
            ADVKATA();
            ADVKATA();
            Income(P_Data[2]) = KataToInteger(CKata);
          }
          else if (IsKataSama(CKata,keyword[14])) {
            ADVKATA();
            ADVKATA();
            Upkeep(P_Data[2]) = KataToInteger(CKata);
          }
          else if (IsKataSama(CKata,keyword[15])) {
            ADVKATA();
            ADVKATA();
            col = KataToInteger(CKata);
            ADVKATA();
            row = KataToInteger(CKata);
            Base(P_Data[2]) = MakePOINT(col,row);
            UpdateBuildingOnMap(&Map_Data,Base(P_Data[2]),'T',2);
            POINT tempC = Base(P_Data[2]);
            Ordinat(tempC)--;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
            Absis(tempC)++; Ordinat(tempC)++;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
            Absis(tempC)--; Ordinat(tempC)++;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
            Absis(tempC)--; Ordinat(tempC)--;
            UpdateBuildingOnMap(&Map_Data,tempC,'C',2);
          }
          ADVKATA();
        }
      }
      ADVKATA();
    }
  }
  /* Starts the game */
  StartGame();
}

void LoadUnitSpecs() {
/* Loads the unit "templates" into TemplateUnit.
   Hasn't checked for any invalid syntax. */
  STARTKATA("unitstats.txt");
  int i = 0;
  while (!EndKata) {
    TemplateType(TemplateUnit[i]) = CKata.TabKata[2];
    ADVKATA();
    TemplateAtkType(TemplateUnit[i]) = CKata.TabKata[1];
    ADVKATA();
    TemplateHP(TemplateUnit[i]) = KataToInteger(CKata);
    ADVKATA();
    TemplateAtk(TemplateUnit[i]) = KataToInteger(CKata);
    TemplateDef(TemplateUnit[i]) = 0;
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
        Kata filename;
        printf("Masukkan nama file yang ingin dibaca : ");
        BacaKata(&filename);
        initialize_game(false,filename.TabKata+1);
      }
    }
    while (execode != 3);
    /* execode == 3 */
    printf("Program exiting. Until next time, then...!\n");
}
