#include <stdio.h>
#include "libs\map.h"


void ViewInfo(MAP M,POINT P){
/* I.S. Map dan point tertentu terdefinisi */
/* F.S. Menampilkan info unit dan building sesuai dengan point tersebut*/	
	int i,j;
	char c;
	i = Absis(P);
	j = Ordinat(P);
	c = Elmt(M,i,j).BData.Type;
	printf("===== CELL INFO =====\n");
	switch (c){
		case 'T' : printf("Tower \n"); printf("Owned by Player %d\n\n",Elmt(M,i,j).BData.owner);break;
		case 'C' : printf("Castle \n"); printf("Owned by Player %d\n\n",Elmt(M,i,j).BData.owner);break;
		case 'V' : printf("Village \n"); printf("Owned by Player %d\n\n",Elmt(M,i,j).BData.owner);break;
		default  : printf("You don't have any building here \n"); break;
	}
	printf("===== UNIT INFO =====\n");
	if(Elmt(M,i,j).CurUnit == Nil){
		printf("You don't have any unit here \n");
	} else {
		switch (UnitType(*Elmt(M,i,j).CurUnit)){
			case 'K' : printf("King \n"); 		printf("Owned by Player %d\n",Owner(*Elmt(M,i,j).CurUnit));break;
			case 'A' : printf("Archer \n");		printf("Owned by Player %d\n",Owner(*Elmt(M,i,j).CurUnit));break;
			case 'S' : printf("Swordsman \n");	printf("Owned by Player %d\n",Owner(*Elmt(M,i,j).CurUnit));break;
			case 'W' : printf("White Mage \n");	printf("Owned by Player %d\n",Owner(*Elmt(M,i,j).CurUnit));break;
		}
		printf("Health %d/%d | ATK %d \n",HP(*Elmt(M,i,j).CurUnit),MaxHP(*Elmt(M,i,j).CurUnit),Attack(*Elmt(M,i,j).CurUnit));
	}
}

void InfoCmd(MAP M){
/* Menampikan info suatu koordinat tertentu */	
	int x,y;
	POINT P;
	printf("Enter coordinate of the cell : ");
	scanf("%d",&x);
	scanf("%d",&y);
	P = MakePOINT(x,y);
	ViewInfo(M,P);
}