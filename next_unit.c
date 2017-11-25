#include <stdio.h>
#include "libs/player.h"

Player P_Data[3]; 
void ChangeUnit(UnitList *P){
	//I.S = UnitList tidak kosong
	//F.S = Select unit baru yang masih punya movement point atau AtkState==true
	ul_address Current = UL_Curr(*P);
	boolean found=false;
	UL_Curr(*P) = UL_Next(UL_Curr(*P));
	if(UL_Curr(*P)==Nil){
			UL_Curr(*P) = UL_First(*P);
	}
	while(UL_Curr(*P)!=Current&&found==false){
		if(UL_Curr(*P)==Nil){
			UL_Curr(*P) = UL_First(*P);
		}
		if(AtkState(UL_Info(UL_Curr(*P)))!=false ||Steps(UL_Info(UL_Curr(*P)))!=0 ){
			found=true;
		}else
		UL_Curr(*P) = UL_Next(UL_Curr(*P));
	}
	if(found==false){
				printf("There is  no more unit that you can select");
			}else{
				printf("You're now selecting ");
				PrintUnitType(UL_Info(UL_Curr(*P)));
				printf("\n");
	}
}
