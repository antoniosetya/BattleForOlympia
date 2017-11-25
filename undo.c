/* UNDO */
#include <stdio.h>
#include "libs/player.h"
#include "libs/stackt.h"
#include "libs/unit.h"
#include "libs/map.h"

Stack UndoMov(int P, int * MovPoint, MAP MovMAP, Stack MovStack){
	POINT currLoc, UndoLoc;
	
	*MovPoint += 1;
	Pop(&MovStack, &currLoc);
	Pop(&MovStack, &UndoLoc);
	
	UpdateUnitOnMap(&MovMAP,UndoLoc,&UL_Info(UL_Curr(Units(P_Data[P]))));
	Elmt(MovMAP,Absis(currLoc),Ordinat(currLoc)).CurUnit = Nil;
	Loc(UL_Info(UL_Curr(Units(P_Data[P])))) = UndoLoc;
	
	return MovStack;
}