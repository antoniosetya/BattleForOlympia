#include <stdio.h>
#include "libs/boolean.h"
#include "libs/player.h"
#include "libs/map.h"

Player P_Data[3];

void End_Turn(int P, MAP *Map_Data) {
	/* Process end turn of a player */
	// Process Income and Upkeep
	Gold(P_Data[P]) = Gold(P_Data[P]) + Income(P_Data[P]) - Upkeep(P_Data[P]);
	// Process the healing effect from any available White Mage
	ul_address Pt = UL_First(Units(P_Data[P]));
	while (Pt != Nil) {
		if (UnitType(UL_Info(Pt)) == 'W') {
			int x = Absis(Loc(UL_Info(Pt)));
			int y = Ordinat(Loc(UL_Info(Pt)));

			if ((Elmt(*Map_Data, x, y+1).CurUnit != Nil) && (Owner(*Elmt(*Map_Data, x, y+1).CurUnit) == P)) {
				HP(*Elmt(*Map_Data, x, y+1).CurUnit) += 10;
				if (HP(*Elmt(*Map_Data, x, y+1).CurUnit) > MaxHP(*Elmt(*Map_Data, x, y+1).CurUnit))
					HP(*Elmt(*Map_Data, x, y+1).CurUnit) = MaxHP(*Elmt(*Map_Data, x, y+1).CurUnit);
			}
			if ((Elmt(*Map_Data, x+1, y).CurUnit != Nil) && (Owner(*Elmt(*Map_Data, x+1, y).CurUnit) == P)) {
				HP(*Elmt(*Map_Data, x+1, y).CurUnit) += 10;
				if (HP(*Elmt(*Map_Data, x+1, y).CurUnit) > MaxHP(*Elmt(*Map_Data, x+1, y).CurUnit))
					HP(*Elmt(*Map_Data, x+1, y).CurUnit) = MaxHP(*Elmt(*Map_Data, x+1, y).CurUnit);
			}
			if ((Elmt(*Map_Data, x, y-1).CurUnit != Nil) && (Owner(*Elmt(*Map_Data, x, y-1).CurUnit) == P)) {
				HP(*Elmt(*Map_Data, x, y-1).CurUnit) += 10;
				if (HP(*Elmt(*Map_Data, x, y-1).CurUnit) > MaxHP(*Elmt(*Map_Data, x, y-1).CurUnit))
					HP(*Elmt(*Map_Data, x, y-1).CurUnit) = MaxHP(*Elmt(*Map_Data, x, y-1).CurUnit);
			}
			if ((Elmt(*Map_Data, x-1, y).CurUnit != Nil) && (Owner(*Elmt(*Map_Data, x-1, y).CurUnit) == P)) {
				HP(*Elmt(*Map_Data, x-1, y).CurUnit) += 10;
				if (HP(*Elmt(*Map_Data, x-1, y).CurUnit) > MaxHP(*Elmt(*Map_Data, x-1, y).CurUnit))
					HP(*Elmt(*Map_Data, x-1, y).CurUnit) = MaxHP(*Elmt(*Map_Data, x-1, y).CurUnit);
			}
		}
		Pt = UL_Next(Pt);
	}
	// Restores all unit movement points & attack state
	Pt = UL_First(Units(P_Data[P]));
	while (Pt != Nil) {
		Steps(UL_Info(Pt)) = MaxSteps(UL_Info(Pt));
		AtkState(UL_Info(Pt)) = true;
		Pt = UL_Next(Pt);
	}
}
