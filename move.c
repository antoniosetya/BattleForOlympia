/* MOVE */
#include <stdio.h>
#include "libs/player.h"
#include "libs/stackt.h"
#include "libs/unit.h"
#include "libs/map.h"

Player P_Data[3]; //Redefining global extern variable from player.h
UTemplate TemplateUnit[4]; // Contains template units
extern VilList FreeVillage;
VilList FreeVillage;

void DrawPossMov (MAP M, int CurrPlayer, int MovPoint, int currX, int currY) {
/* I.S. M terdefinisi */
/* F.S. Tergambar M(i,j), dengan nomor kolom dan baris di pinggir map dan format setiap cell :
    *****
    * K *
    * U *
    *   *
    *****
    K = Bangunan yang ada di cell map. Jika K = N (Normal), diprint kosong
    U = Unit yang ada dalam cell itu */
  int i, j;
  printf("    ");
  // Prints cell numbers
  for (j = 1;j <= NKol(M); j++) {
    printf(" %3d ",j);
  }
  printf("\n    ");
  for (j = 1;j <= NKol(M); j++) {
    printf("*****");
  }
  printf("\n");
  for (i = 1;i <= NBrs(M); i++) {
    printf("    ");
    // Prints available building on this cell
    for (j = 1;j <= NKol(M); j++) {
      if (Elmt(M,j,i).BData.Type != 'N') {
        if (Elmt(M,j,i).BData.owner != 0) {
          printf("* %s%c%s *",P_Data[Elmt(M,j,i).BData.owner].Color,Elmt(M,j,i).BData.Type,NORMAL);
        }
        else {
          printf("* %c *",Elmt(M,j,i).BData.Type);
        }
      }
      else {
        printf("*   *");
      }
    }
    printf("\n");
    printf("%3d ",i); // Prints row number
    POINT temp;
    // Prints any unit that occupy this cell
    for (j = 1;j <= NKol(M); j++) {
      if (Elmt(M,j,i).CurUnit != Nil) {
        temp = MakePOINT(j,i);
        if (EQ(temp,Loc(UL_Info(UL_Curr(Units(P_Data[CurrPlayer])))))) {
          printf("* %s%c%s *",GREEN,UnitType(*Elmt(M,j,i).CurUnit),NORMAL);
        }
        else {
          printf("* %s%c%s *",P_Data[Owner(*Elmt(M,j,i).CurUnit)].Color,UnitType(*Elmt(M,j,i).CurUnit),NORMAL);
        }
      }
      else {
        printf("*   *");
      }
    }
    printf("\n    ");
    for (j = 1;j <= NKol(M); j++) {
      temp = MakePOINT(j,i);
			if (sqrt(pow((Absis(temp)-currX),2) + pow((Ordinat(temp)-currY),2)) <= MovPoint)
				printf("* # *");
			else
			  printf("*   *");
    }
    printf("\n    ");
    for (j = 1;j <= NKol(M); j++) {
      printf("*****");
    }
    printf("\n");
  }
}

void MoveCurrUnit(int P, int * MovPoint, MAP *MovMAP, Stack *MovStack){
	ul_address Ptemp = UL_Curr(Units(P_Data[P]));
	boolean moved;
	POINT temp, currLoc;
	int CoorX, CoorY, tempAbsis, tempOrdinat;
	int index;

	// (Loc(UL_Info(UL_Curr((Units(P_Data[P])))))))
	int currX = Absis(Loc(UL_Info(UL_Curr(Units(P_Data[P])))));
	int currY = Ordinat(Loc(UL_Info(UL_Curr(Units(P_Data[P])))));

	DrawPossMov(*MovMAP,P,*MovPoint,currX,currY);
	printf("  # : Moveable location\n");
	//do {
		printf("\nPlease enter cell’s coordinate x y (seperated by a space): ");
		scanf("%d%d", &CoorX, &CoorY);
		printf("\n");
		temp = MakePOINT(CoorX,CoorY);
		currLoc = MakePOINT(currX,currY);
    float distance = sqrt(pow((Absis(temp)-currX),2) + pow((Ordinat(temp)-currY),2));
		if (distance <= Steps(UL_Info(Ptemp)) && (Elmt(*MovMAP,Absis(temp),Ordinat(temp)).CurUnit == Nil)) {
			UpdateUnitOnMap(MovMAP,temp,&UL_Info(UL_Curr(Units(P_Data[P]))));
			UpdateUnitOnMap(MovMAP,currLoc,Nil);
			Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = temp;
			Push(MovStack,currLoc);
			Steps(UL_Info(Ptemp)) -= ceil(distance);
      printf("Successfully moved to ");TulisPOINT(temp);printf("\n");
      // Village acquisition
      if (BuildType(Elmt(*MovMAP,Absis(temp),Ordinat(temp)).BData) == 'V') {
        B_Data tempVil;
        vl_address targetVil;
        BuildType(tempVil) = 'V';
        BuildPos(tempVil) = temp;
        if (BuildOwner(Elmt(*MovMAP,Absis(temp),Ordinat(temp)).BData) == 0) {
          BuildOwner(tempVil) = 0;
          VL_DeleteP(&FreeVillage,tempVil,&targetVil);
          BuildOwner(VL_Info(targetVil)) = P;
          VL_InsertFirst(&Villages(P_Data[P]),targetVil);
          UpdateBuildingOnMap(MovMAP,temp,'V',P);
          Income(P_Data[P])+=75;
          printf("Acquired an empty village!\n");
        }
        else {
          if (BuildOwner(Elmt(*MovMAP,Absis(temp),Ordinat(temp)).BData) != P) {
            if (P == 1) {
              BuildOwner(tempVil) = 2;
              VL_DeleteP(&Villages(P_Data[2]),tempVil,&targetVil);
              Income(P_Data[2])-=75;
              BuildOwner(VL_Info(targetVil)) = P;
              VL_InsertFirst(&Villages(P_Data[P]),targetVil);
              UpdateBuildingOnMap(MovMAP,temp,'V',P);
              Income(P_Data[P])+=75;
            }
            else {
              BuildOwner(tempVil) = 1;
              VL_DeleteP(&Villages(P_Data[1]),tempVil,&targetVil);
              Income(P_Data[2])-=75;
              BuildOwner(VL_Info(targetVil)) = P;
              VL_InsertFirst(&Villages(P_Data[P]),targetVil);
              UpdateBuildingOnMap(MovMAP,temp,'V',P);
              Income(P_Data[P])+=75;
            }
            printf("Acquired a village!\n");
          }
        }
      }
		}
    else
      printf("You can’t move there\n");
}
