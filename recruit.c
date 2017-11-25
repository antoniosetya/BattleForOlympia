#include "libs/map.h"
#include <stdio.h>

Player P_Data[3]; //Redefining global extern variable from player.h
UTemplate TemplateUnit[4]; // Contains template units

void Recruit(int P, MAP Map_Data) {
	if (UnitType(UL_Info(UL_Curr(Units(P_Data[P])))) != 'K') {
		printf("Only King(s) can recruit!\n\n");
	}
	else if ((UnitType(UL_Info(UL_Curr(Units(P_Data[P])))) == 'K') && NEQ(Loc(UL_Info(UL_Curr(Units(P_Data[P])))), Base(P_Data[P]))) {
		printf("King is not at the tower\n\n");
	}
	else {
		if (Gold(P_Data[P]) <= 0)
			printf("You don't have any gold\n\n");
		else {
			POINT castle_p;
			printf("Enter coordinate of empty castle: ");
			BacaPOINT(&castle_p);
			while ((Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type != 'C') || ((Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type == 'C') && (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit != Nil))){
				if (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type != 'C')
					printf("There's is no castle here\n");
				else if ((Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type == 'C') && (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit != Nil))
					printf("Castle is occupied\n");
				printf("Enter coordinate of empty castle: ");
				BacaPOINT(&castle_p);
			}		
			int unit_type;
			printf("\n=== List of Recruits ===\n");
			printf("1. Archer | Health %d | ATK %d | AtkType: %c | Steps: %d | %dG | Upkeep Cost: %d\n", TemplateUnit[1].MaxHP, TemplateUnit[1].Atk, TemplateUnit[1].AtkType, TemplateUnit[1].maxSteps, TemplateUnit[1].Price, TemplateUnit[1].UpkeepCost);
			printf("2. Swordsman | Health %d | ATK %d | AtkType: %c | Steps: %d | %dG | Upkeep Cost: %d\n", TemplateUnit[2].MaxHP, TemplateUnit[2].Atk, TemplateUnit[2].AtkType, TemplateUnit[2].maxSteps, TemplateUnit[2].Price, TemplateUnit[1].UpkeepCost);
			printf("3. White Mage | Health %d | ATK %d | AtkType: %c | Steps: %d | %dG | Upkeep Cost: %d\n", TemplateUnit[3].MaxHP, TemplateUnit[3].Atk, TemplateUnit[3].AtkType, TemplateUnit[3].maxSteps, TemplateUnit[3].Price, TemplateUnit[1].UpkeepCost);
			printf("Enter no. of unit you want to recruit: ");
			scanf("%d",&unit_type);

			while (unit_type < 1 || unit_type > 3) {
				printf("Input invalid, try again\n");
				printf("Enter no. of unit you want to recruit: ");
				scanf("%d",&unit_type);
			}

			if (unit_type == 1) {
				if (Gold(P_Data[P]) < TemplateUnit[1].Price)
					printf("Not enough money\n");
				else {
					Unit recruit_unit;
					InitUnit(&recruit_unit, TemplateUnit[1], P, castle_p);
					UL_InsVLast(&Units(P_Data[P]), recruit_unit);
					Gold(P_Data[P]) -= TemplateUnit[1].Price;
					Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit = 'A';
					printf("You have recruited an archer!\n\n");
				}
			}
			else if (unit_type == 2) {
				if (Gold(P_Data[P]) < TemplateUnit[2].Price)
					printf("Not enough money\n");
				else {
					Unit recruit_unit;
					InitUnit(&recruit_unit, TemplateUnit[2], P, castle_p);
					UL_InsVLast(&Units(P_Data[P]), recruit_unit);
					Gold(P_Data[P]) -= TemplateUnit[2].Price;
					Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit = 'S';
					printf("You have recruited a swordsman!\n\n");
				}
			}
			else if (unit_type == 3) {
				if (Gold(P_Data[P]) < TemplateUnit[3].Price)
					printf("Not enough money\n");
				else {
					Unit recruit_unit;
					InitUnit(&recruit_unit, TemplateUnit[3], P, castle_p);
					UL_InsVLast(&Units(P_Data[P]), recruit_unit);
					Gold(P_Data[P]) -= TemplateUnit[3].Price;
					Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit = 'W';
					printf("You have recruited a white mage!\n\n");
				}
			}
		}
	}
}
