#include "libs/map.h"
#include <stdio.h>

Player P_Data[3]; //Redefining global extern variable from player.h
UTemplate TemplateUnit[4]; // Contains template units

void GenerateUnit(MAP *Map_Data, int P, char type, POINT loc) {
/* Generetes desired unit and updates the map */
	int code;
	switch (type) {
		case 'K':
			code = 0;break;
		case 'A':
			code = 1;break;
		case 'S':
			code = 2;break;
		case 'W':
			code = 3;break;
		default:
			code = -999;
	}
	if (code == -999) {
		printf("GenerateUnitError : Invalid unit type!\n");
	}
	else if ((P <= 0) || (P > 2)) {
		printf("GenerateUnitError : Invalid player!\n");
	}
	else {
		Unit recruit_unit;
		InitUnit(&recruit_unit, TemplateUnit[code], P, loc);
		ul_address unitadr = UL_Alokasi(recruit_unit);
		UL_InsertLast(&Units(P_Data[P]),unitadr);
		UpdateUnitOnMap(Map_Data,loc,&UL_Info(unitadr));
	}
}

void Recruit(int P, MAP *Map_Data) {
	if (UnitType(UL_Info(UL_Curr(Units(P_Data[P])))) != 'K') {
		printf("Only King that can recruit unit(s)!\n\n");
	}
	else if ((UnitType(UL_Info(UL_Curr(Units(P_Data[P])))) == 'K') && NEQ(Loc(UL_Info(UL_Curr(Units(P_Data[P])))), Base(P_Data[P]))) {
		printf("King is not at the tower\n\n");
	}
	else {
		if (Gold(P_Data[P]) <= 0)
			printf("You don't have any gold\n\n");
		else {
			POINT castle_p;
			boolean cancel = false;
			boolean valid = false;
			POINT Pcancel = MakePOINT(0,0);
			do {
				printf("Enter coordinate of your empty castle (input 0 0 to cancel): ");
				BacaPOINT(&castle_p);
				cancel = EQ(castle_p,Pcancel);
				if (!cancel) {
					if (((Absis(castle_p) > NKol(*Map_Data)) || (Absis(castle_p) < 0)) && ((Ordinat(castle_p) > NBrs(*Map_Data)) || (Ordinat(castle_p) < 0)))
						printf("That location is out of map's range!\n");
					else {
						if (Elmt(*Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type != 'C')
							printf("There's is no castle here!\n");
						else if (Elmt(*Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.owner != P)
							printf("That's not your castle!\n");
						else if (Elmt(*Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit != Nil)
							printf("Castle is occupied. Pick another one\n");
					}
					valid = !(((Absis(castle_p) > NKol(*Map_Data)) || (Absis(castle_p) < 0)) && ((Ordinat(castle_p) > NBrs(*Map_Data)) || (Ordinat(castle_p) < 0))) && (Elmt(*Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type == 'C') && (Elmt(*Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.owner == P) && (Elmt(*Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit == Nil);
				}
			}
			while (!valid && !cancel);
			if (cancel) {
				printf("Cancelled recruiting a unit...\n");
			}
			else {
				int unit_type;
				printf("\n=== List of Recruits ===\n");
				printf("1. Archer | Health %d | ATK %d | AtkType: %c | Steps: %d | %dG | Upkeep Cost: %d\n", TemplateUnit[1].MaxHP, TemplateUnit[1].Atk, TemplateUnit[1].AtkType, TemplateUnit[1].maxSteps, TemplateUnit[1].Price, TemplateUnit[1].UpkeepCost);
				printf("2. Swordsman | Health %d | ATK %d | AtkType: %c | Steps: %d | %dG | Upkeep Cost: %d\n", TemplateUnit[2].MaxHP, TemplateUnit[2].Atk, TemplateUnit[2].AtkType, TemplateUnit[2].maxSteps, TemplateUnit[2].Price, TemplateUnit[2].UpkeepCost);
				printf("3. White Mage | Health %d | ATK %d | AtkType: %c | Steps: %d | %dG | Upkeep Cost: %d\n", TemplateUnit[3].MaxHP, TemplateUnit[3].Atk, TemplateUnit[3].AtkType, TemplateUnit[3].maxSteps, TemplateUnit[3].Price, TemplateUnit[3].UpkeepCost);
				printf("Enter no. of unit you want to recruit: ");
				scanf("%d",&unit_type);

				while (unit_type < 1 || unit_type > 3) {
					printf("Input invalid, try again\n");
					printf("Enter no. of unit you want to recruit: ");
					scanf("%d",&unit_type);
				}

				if (Gold(P_Data[P]) < Price(TemplateUnit[unit_type])) {
					printf("Not enough money\n");
				}
				else {
					GenerateUnit(Map_Data,P,TemplateType(TemplateUnit[unit_type]),castle_p);
					Gold(P_Data[P]) -= Price(TemplateUnit[unit_type]);
					Upkeep(P_Data[P]) += UpkeepCost(TemplateUnit[unit_type]);
					printf("You have recruited an ");
					switch(unit_type) {
						case 1:
							printf(" Archer");
							break;
						case 2:
							printf(" Swordsman");
							break;
						case 3:
							printf(" White Mage");
							break;
					}
					printf("!\n");
				}
			}
		}
	}
}
