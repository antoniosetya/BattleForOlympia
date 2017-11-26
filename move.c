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

void DrawPossMov (MAP M, int CurrPlayer, int MovPoint, int currX, int currY, POINT availSpot[], int Neffavail) {
/* I.S. M terdefinisi */
/* F.S. Tergambar M(i,j), dengan nomor kolom dan baris di pinggir map dan format setiap cell :
    *****
    * K *
    * U *
    * # *
    *****
    K = Bangunan yang ada di cell map. Jika K = N (Normal), diprint kosong
    U = Unit yang ada dalam cell itu
    # = Jika bisa berpindah ke petak ini, maka # akan tercetak */
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
			boolean found = false;
      int k = 0;
      while ((k < Neffavail) && !found) {
        found = EQ(temp,availSpot[k]);
        if (!found) {
          k++;
        }
      }
      if (found) {
        printf("* # *");
      }
      else {
        printf("*   *");
      }
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
  currLoc = Loc(UL_Info(Ptemp));
	int CoorX, CoorY, tempAbsis, tempOrdinat;
	int index;

	// (Loc(UL_Info(UL_Curr((Units(P_Data[P])))))))
	int currX = Absis(Loc(UL_Info(Ptemp)));
	int currY = Ordinat(Loc(UL_Info(Ptemp)));

  POINT availSpot[NBrs(*MovMAP) * NKol(*MovMAP)];
  int i, j;
  int Neffavail = 0;
  boolean UnitIsHere = false;
  /* Storing which position this unit can move
     This has to be employed rather than using the calculated distance,
     because it cannot move through another unit when moving */
  // Checking the right side
  for (i = currX+1;((i - currX) <= *MovPoint) && (i <= NKol(*MovMAP)) && !UnitIsHere;i++) {
    if (Elmt(*MovMAP,i,currY).CurUnit != Nil) {
      UnitIsHere = true;
    }
    else {
      availSpot[Neffavail] = MakePOINT(i,currY);
      Neffavail++;
    }
  }
  // Checking the left side
  UnitIsHere = false;
  for (i = currX-1;((currX - i) <= *MovPoint) && (i > 0) && !UnitIsHere;i--) {
    if (Elmt(*MovMAP,i,currY).CurUnit != Nil) {
      UnitIsHere = true;
    }
    else {
      availSpot[Neffavail] = MakePOINT(i,currY);
      Neffavail++;
    }
  }
  // Checking the top side
  UnitIsHere = false;
  for (j = currY+1;((j - currY) <= *MovPoint) && (j <= NBrs(*MovMAP)) && !UnitIsHere;j++) {
    if (Elmt(*MovMAP,currX,j).CurUnit != Nil) {
      UnitIsHere = true;
    }
    else {
      availSpot[Neffavail] = MakePOINT(currX,j);
      Neffavail++;
    }
  }
  // Checking the bottom side
  UnitIsHere = false;
  for (j = currY-1;((currY - j) <= *MovPoint) && (j > 0) && !UnitIsHere;j--) {
    if (Elmt(*MovMAP,currX,j).CurUnit != Nil) {
      UnitIsHere = true;
    }
    else {
      availSpot[Neffavail] = MakePOINT(currX,j);
      Neffavail++;
    }
  }

	DrawPossMov(*MovMAP,P,*MovPoint,currX,currY, availSpot, Neffavail);
	printf("  # : Moveable location\n");

	printf("\nPlease enter cell’s coordinate x y (separated by a space): ");
	scanf("%d%d", &CoorX, &CoorY);
	printf("\n");

  temp = MakePOINT(CoorX,CoorY);
  boolean found = false;
  int k = 0;
  while ((k < Neffavail) && !found) {
    found = EQ(temp,availSpot[k]);
    if (!found) {
      k++;
    }
  }

	if (found) {
		UpdateUnitOnMap(MovMAP,temp,&UL_Info(UL_Curr(Units(P_Data[P]))));
		UpdateUnitOnMap(MovMAP,currLoc,Nil);
		Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = temp;
		Push(MovStack,currLoc);
		Steps(UL_Info(Ptemp)) -= ceil(Panjang(temp,currLoc));
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
        Steps(UL_Info(Ptemp)) = 0;
      }
      else {
        if (BuildOwner(Elmt(*MovMAP,Absis(temp),Ordinat(temp)).BData) != P) {
          if (P == 1) {
            BuildOwner(tempVil) = 2;
            VL_DeleteP(&Villages(P_Data[2]),tempVil,&targetVil);
            Income(P_Data[1])-=75;
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
          printf("Acquired a village from the enemy!\n");
          Steps(UL_Info(Ptemp)) = 0;
        }
      }
    }
	}
  else
    printf("You can’t move there\n");
}
