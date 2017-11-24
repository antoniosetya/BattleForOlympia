#include "libs/map.h"
#include <stdio.h>

Player P_Data[3]; //Redefining global extern variable from player.h

//Prosedur Recruit masih perlu perbaikan
void Recruit(int P, MAP Map_Data) {
	if (UnitType(UL_Info(UL_Curr(Units(P_Data[P])))) != 'K') {
		printf("Only King(s) can recruit!\n");
	}
	else {
		POINT castle_p;
		printf("Enter coordinate of empty castle: ");
		BacaPOINT(&castle_p);
		while (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type != 'C') {
			printf("There is no castle here!\n");
			printf("Enter coordinate of empty castle: ");
			BacaPOINT(&castle_p);
		}
		if (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).BData.Type == 'C') {
			while (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit != Nil) {
				printf("That castle is occupied!\n");
				printf("Enter coordinate of empty castle: ");
				BacaPOINT(&castle_p);
			}
				
			if (Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit == Nil) {
				int unit_type;
				//Default stats dari tiap unit belum benar
				printf("\n=== List of Recruits ===\n");
				printf("1. Archer | Health 20 | ATK 4 | DEF 1 | 50G\n");
				printf("2. Swordsman | Health 20 | ATK 3 | DEF 2 | 40G\n");
				printf("3. White Mage | Health | ATK | DEF | 60G\n");
				printf("Enter no. of unit you want to recruit: ");
				scanf("%d",&unit_type);

				while (unit_type < 1 || unit_type > 3) {
					printf("Input invalid, try again\n");
					printf("Enter no. of unit you want to recruit: ");
					scanf("%d",&unit_type);
				}

				if (unit_type == 1) {
					if (Gold(P_Data[P]) < 50)
						printf("Not enough money\n");
					else {
						Unit recruit_unit;
						//Stats template belum benar
						UTemplate recruit_temp;
						TemplateType(recruit_temp) = 'A';
						TemplateAtkType(recruit_temp) = 'M';
						TemplateHP(recruit_temp) = 100;
						TemplateAtk(recruit_temp) = 50;
						TemplateDef(recruit_temp)= 50;
						TemplateSteps(recruit_temp) = 2;
						UpkeepCost(recruit_temp) = 50;
						Price(recruit_temp) = 50;
						
						InitUnit(&recruit_unit, recruit_temp, P, castle_p);
						UL_InsVLast(&Units(P_Data[P]), recruit_unit);
						Gold(P_Data[P]) -= 50;
						Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit = 'A';
						printf("You have recruited an archer!\n\n");
					}
				}
				else if (unit_type == 2) {
					if (Gold(P_Data[P]) < 40)
						printf("Not enough money\n");
					else {
						Unit recruit_unit;
						//Stats template belum benar
						UTemplate recruit_temp;
						TemplateType(recruit_temp) = 'S';
						TemplateAtkType(recruit_temp) = 'M';
						TemplateHP(recruit_temp) = 100;
						TemplateAtk(recruit_temp) = 50;
						TemplateDef(recruit_temp)= 50;
						TemplateSteps(recruit_temp) = 2;
						UpkeepCost(recruit_temp) = 50;
						Price(recruit_temp) = 50;
						
						InitUnit(&recruit_unit, recruit_temp, P, castle_p);
						UL_InsVLast(&Units(P_Data[P]), recruit_unit);
						Gold(P_Data[P]) -= 40;
						Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit = 'S';
						printf("You have recruited a swordsman!\n\n");
					}
				}
				else if (unit_type == 3) {
					if (Gold(P_Data[P]) < 60)
						printf("Not enough money\n");
					else {
						Unit recruit_unit;
						//Stats template belum benar
						UTemplate recruit_temp;
						TemplateType(recruit_temp) = 'W';
						TemplateAtkType(recruit_temp) = 'M';
						TemplateHP(recruit_temp) = 100;
						TemplateAtk(recruit_temp) = 50;
						TemplateDef(recruit_temp)= 50;
						TemplateSteps(recruit_temp) = 2;
						UpkeepCost(recruit_temp) = 50;
						Price(recruit_temp) = 50;
						
						InitUnit(&recruit_unit, recruit_temp, P, castle_p);
						UL_InsVLast(&Units(P_Data[P]), recruit_unit);
						Gold(P_Data[P]) -= 60;
						Elmt(Map_Data, Absis(castle_p), Ordinat(castle_p)).CurUnit = 'W';
						printf("You have recruited a white mage!\n\n");
					}
				}
			}
		}
	}
}
