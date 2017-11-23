#include <stdio.h>
#include "libs/player.h"

Player P_Data[3]; //Redefining global extern variable from player.h

void ChangeUnit(int P,ul_address *CurrUnit){
/* I.S. Sembarang Player P terdefinisi */
/* F.S. List unit dari Player P ditampilkan ke layar */
	int num = 1;
	int pil;
	UnitList U=Units(P_Data[P]);
	ul_address N=UL_First(U);
	if(UL_IsEmpty(U)){
		printf("You don't have any unit to select. \n");
		CurrUnit = Nil;
	} else {
		printf("=======LIST OF UNITS=======\n");
		while(N!=Nil){
			printf("%d. ",num);
			PrintUnitType(UL_Info(N));
			TulisPOINT(Loc(UL_Info(N)));
			printf(" | Health %d\n",HP(UL_Info(N)));
			N = UL_Next(N);
			num++;
		}
		printf("Please enter the number of unit you want to select : ");
		scanf("%d",&pil);
		num = 1;
		N = UL_First(U);
		while(num < pil){
			N = UL_Next(N);
			num++;
		}
		printf("You're now selecting ");
		PrintUnitType(UL_Info(N));
		printf("\n");
		*CurrUnit = N;
	}
}
