/* MOVE */
#include <stdio.h>
#include "libs/player.h"
#include "libs/stackt.h"
#include "libs/unit.h"
#include "libs/map.h"

Player P_Data[3]; //Redefining global extern variable from player.h
UTemplate TemplateUnit[4]; // Contains template units

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
      temp = MakePOINT(j,i);
      if (Elmt(M,j,i).CurUnit != Nil) {
        if (EQ(temp,Loc(UL_Info(UL_Curr(Units(P_Data[CurrPlayer])))))) {
          printf("* %s%c%s *",GREEN,UnitType(*Elmt(M,j,i).CurUnit),NORMAL);
        }
        else {
          printf("* %s%c%s *",P_Data[Owner(*Elmt(M,j,i).CurUnit)].Color,UnitType(*Elmt(M,j,i).CurUnit),NORMAL);
        }
      }
      else {
		if (MovPoint == 1){
			if ((abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 0) || (abs(Ordinat(temp)-currY) == 1 && abs(Absis(temp)-currX) == 0))
				printf("* # *");
			else
			printf("*   *");
		}
		else if (MovPoint == 2){
			if ((abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 0) || (abs(Ordinat(temp)-currY) == 1 && abs(Absis(temp)-currX) == 0) || (abs(Absis(temp)-currX) == 2 && abs(Ordinat(temp)-currY) == 0) || (abs(Ordinat(temp)-currY) == 2 && abs(Absis(temp)-currX) == 0) || ((abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 1) || (abs(Ordinat(temp)-currY) == 1 && abs(Absis(temp)-currX) == 1)))
				printf("* # *");
			else
				printf("*   *");
			
		}
      }
    }
    printf("\n    ");
    for (j = 1;j <= NKol(M); j++) {
      printf("*   *");
    }
    printf("\n    ");
    for (j = 1;j <= NKol(M); j++) {
      printf("*****");
    }
    printf("\n");
  }
}

Stack MoveCurrUnit(int P, int * MovPoint, MAP MovMAP, Stack MovStack){
	ul_address Ptemp = UL_Curr(Units(P_Data[P]));
	boolean moved;
	POINT temp, currLoc;
	int CoorX, CoorY, tempAbsis, tempOrdinat;
	int index;
	
	// (Loc(UL_Info(UL_Curr((Units(P_Data[P])))))))
	moved = false;
	int currX = Absis(Loc(UL_Info(UL_Curr(Units(P_Data[P])))));
	int currY = Ordinat(Loc(UL_Info(UL_Curr(Units(P_Data[P])))));
	
	DrawPossMov(MovMAP,P,*MovPoint,currX,currY);
	printf("  # : Moveable location\n");
	do{
		printf("\nPlease enter cell’s coordinate x y (seperated by a space): ");
		scanf("%d%d", &CoorX, &CoorY);
		printf("\n");
		temp = MakePOINT(CoorX,CoorY);
		currLoc = MakePOINT(currX,currY);
		if (*MovPoint == 1){
			if ((abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 0) || (abs(Ordinat(temp)-currY) == 1 && abs(Absis(temp)-currX) == 0)){
				UpdateUnitOnMap(&MovMAP,temp,&UL_Info(UL_Curr(Units(P_Data[P]))));
				Elmt(MovMAP,Absis(currLoc),Ordinat(currLoc)).CurUnit = Nil;
				Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = PlusDelta(Loc(UL_Info(UL_Curr(Units(P_Data[P])))),Absis(temp)-Absis(currLoc),Ordinat(temp)-Ordinat(currLoc));
				Push(&MovStack,currLoc);
				Push(&MovStack,temp);
				* MovPoint -= 1;
				moved = true;
			}
			else
				printf("You can’t move there\n");
		}
		else if (*MovPoint == 2){
			if ((abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 0) || (abs(Ordinat(temp)-currY) == 1 && abs(Absis(temp)-currX) == 0) || (abs(Absis(temp)-currX) == 2 && abs(Ordinat(temp)-currY) == 0) || (abs(Ordinat(temp)-currY) == 2 && abs(Absis(temp)-currX) == 0) || ((abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 1) || (abs(Ordinat(temp)-currY) == 1 && abs(Absis(temp)-currX) == 1)))
				if ((abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 0) || (abs(Ordinat(temp)-currY) == 1 && abs(Absis(temp)-currX) == 0)){
					UpdateUnitOnMap(&MovMAP,temp,&UL_Info(UL_Curr(Units(P_Data[P]))));
					Elmt(MovMAP,Absis(currLoc),Ordinat(currLoc)).CurUnit = Nil;
					Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = PlusDelta(Loc(UL_Info(UL_Curr(Units(P_Data[P])))),Absis(temp)-Absis(currLoc),Ordinat(temp)-Ordinat(currLoc));
					Push(&MovStack,currLoc);
					Push(&MovStack,temp);
					* MovPoint -= 1;
					moved = true;
				} else{
					if (abs(Absis(temp)-currX) == 1 && abs(Ordinat(temp)-currY) == 1){
						tempAbsis = CoorX - currX;
						temp = MakePOINT(currX+tempAbsis,currY);
						Push(&MovStack,currLoc);
						Push(&MovStack,temp);
						Push(&MovStack,temp);
						tempOrdinat = CoorY - currY;
						temp = MakePOINT(Absis(temp),currY+tempOrdinat);
						UpdateUnitOnMap(&MovMAP,temp,&UL_Info(UL_Curr(Units(P_Data[P]))));
						Elmt(MovMAP,Absis(currLoc),Ordinat(currLoc)).CurUnit = Nil;
						Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = PlusDelta(Loc(UL_Info(UL_Curr(Units(P_Data[P])))),Absis(temp)-Absis(currLoc),Ordinat(temp)-Ordinat(currLoc));
						Push(&MovStack,temp);
						* MovPoint -= 2;
						moved = true;
					} else if (abs(Absis(temp)-currX) == 2 && abs(Ordinat(temp)-currY) == 0){
						tempAbsis = (CoorX - currX)/2;
						temp = MakePOINT(currX+tempAbsis,currY);
						Push(&MovStack,currLoc);
						Push(&MovStack,temp);
						Push(&MovStack,temp);
						temp = MakePOINT(Absis(temp)+tempAbsis,currY);
						UpdateUnitOnMap(&MovMAP,temp,&UL_Info(UL_Curr(Units(P_Data[P]))));
						Elmt(MovMAP,Absis(currLoc),Ordinat(currLoc)).CurUnit = Nil;
						Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = PlusDelta(Loc(UL_Info(UL_Curr(Units(P_Data[P])))),Absis(temp)-Absis(currLoc),Ordinat(temp)-Ordinat(currLoc));
						Push(&MovStack,temp);
						* MovPoint -= 2;
						moved = true;
					} else if (abs(Absis(temp)-currX) == 2 && abs(Ordinat(temp)-currY) == 0){
						tempOrdinat = (CoorY - currY)/2;
						temp = MakePOINT(currX,currY+tempOrdinat);
						Push(&MovStack,currLoc);
						Push(&MovStack,temp);
						Push(&MovStack,temp);
						temp = MakePOINT(currX,Ordinat(temp)+tempOrdinat);
						UpdateUnitOnMap(&MovMAP,temp,&UL_Info(UL_Curr(Units(P_Data[P]))));
						Elmt(MovMAP,Absis(currLoc),Ordinat(currLoc)).CurUnit = Nil;
						Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = PlusDelta(Loc(UL_Info(UL_Curr(Units(P_Data[P])))),Absis(temp)-Absis(currLoc),Ordinat(temp)-Ordinat(currLoc));
						Push(&MovStack,temp);
						* MovPoint -= 2;
						moved = true;
					}
				}
			else
				printf("You can’t move there\n");
		}
	} while (!moved);
	
	return MovStack;
}