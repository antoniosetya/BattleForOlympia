/* UNDO */
#include <stdio.h>
#include "libs/player.h"
#include "libs/stackt.h"
#include "libs/unit.h"
#include "libs/map.h"

Player P_Data[3];

void UndoMov(int P, MAP * MovMAP, Stack * MovStack) {
	POINT currLoc, UndoLoc;
	currLoc = Loc(UL_Info(UL_Curr(Units(P_Data[P]))));
	Pop(MovStack,&UndoLoc);
	float distance = sqrt(pow((Absis(UndoLoc)-Absis(currLoc)),2) + pow((Ordinat(UndoLoc)-Ordinat(currLoc)),2));
	Steps(UL_Info(UL_Curr(Units(P_Data[P])))) += ceil(distance);

	UpdateUnitOnMap(MovMAP,UndoLoc,&UL_Info(UL_Curr(Units(P_Data[P]))));
	UpdateUnitOnMap(MovMAP,currLoc,Nil);
	Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = UndoLoc;
}
