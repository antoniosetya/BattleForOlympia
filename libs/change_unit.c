#include <stdio.h>
#include "player.h"

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

void ViewUnit(Player P,Unit *CurrUnit){
/* I.S. Sembarang Player P terdefinisi */
/* F.S. List unit dari Player P ditampilkan ke layar */
	int num = 1;
	int pil;
	UnitList U=Units(P);
	ul_address N=First(U); 
	if(UL_IsEmpty(U)){
		printf("You don't have any unit to select. \n");	
	} else {
		printf("=======LIST OF UNITS=======\n");
		while(N!=Nil){
			printf("%d. ",num);
			PrintUnitType(Info(N));
			TulisPOINT(Loc(Info(N)));
			printf(" | Health %d\n",HP(Info(N)));
			N = Next(N);
			num++;
		}
	}

	printf("Please enter the number of unit you want to select : ");
	scanf("%d",&pil);
	num = 1;
	N = First(U);
	while(num < pil){
		N = Next(N);
		num++;
	}
	printf("You're now selected ");
	PrintUnitType(Info(N));
	*CurrUnit = Info(N);
}