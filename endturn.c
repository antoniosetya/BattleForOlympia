#include <stdio.h>
#include "libs/player.h"
#include "libs/map.h"

Player P_Data[3];
MAP Map_Data;

void End_Turn(int P) {
	boolean found = false;
	while (!found && (UL_Next(UL_Curr(Units(P_Data[P])))) != Nil) {
		if (UnitType(UL_Info(UL_Curr(Units(P_Data[P])))) == 'W') {
			found = true;
		}
	}
	if (found) {
		int x = Absis(Loc(UL_Info(UL_Curr(Units(P_Data[P])))));
		int y = Ordinat(Loc(UL_Info(UL_Curr(Units(P_Data[P])))));
		
		if ((Elmt(Map_Data, x, y+1).CurUnit != Nil) && (Owner(*Elmt(Map_Data, x, y+1).CurUnit) == P)) {
			HP(*Elmt(Map_Data, x, y+1).CurUnit) += 10;
		}
		if ((Elmt(Map_Data, x+1, y).CurUnit != Nil) && (Owner(*Elmt(Map_Data, x+1, y).CurUnit) == P)) {
			HP(*Elmt(Map_Data, x+1, y).CurUnit) += 10;
		}
		if ((Elmt(Map_Data, x, y-1).CurUnit != Nil) && (Owner(*Elmt(Map_Data, x, y-1).CurUnit) == P)) {
			HP(*Elmt(Map_Data, x, y-1).CurUnit) += 10;
		}
		if ((Elmt(Map_Data, x-1, y).CurUnit != Nil) && (Owner(*Elmt(Map_Data, x-1, y).CurUnit) == P)) {
			HP(*Elmt(Map_Data, x-1, y).CurUnit) += 10;
		}
	}
}
