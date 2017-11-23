#include <stdio.h>
#include "libs\player.h"

void PrintUnitType(Unit U){
/* I.S. Sembarang Unit U terdefinisi*/
/* F.S. Print tipe Unit U berdasarkan singkatannya*/
	switch (UnitType(U)){
		case 'K' : printf("King ");			break;
		case 'A' : printf("Archer ");		break;
		case 'S' : printf("Swordsman ");	break;
		case 'W' : printf("White Mage ");	break;
	}
}

void ChangeUnit(Player P,ul_address *CurrUnit){
/* I.S. Sembarang Player P terdefinisi */
/* F.S. List unit dari Player P ditampilkan ke layar */
	int num = 1;
	int pil;
	UnitList U=Units(P);
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
		*CurrUnit = N;
	}
}