#include "../UnitList.h"
#include <stdio.h>
#include "../point.h"

/*Driver dari ListLinear
 * Elemen dari List dibedakan berdasarkan letak posisinya.
 * */
void initdummy(Unit *U,POINT Loc){
	UnitType(*U) ='D';
  MaxHP(*U) = 100;
  HP(*U) = 100;
  Attack(*U) = 100;
  AttackType(*U) = 'M';
  Def(*U) = 100;
  MaxSteps(*U) = 100;
  Steps(*U) = 100;
  AtkState(*U) = true;
  Loc(*U) = Loc;
  Owner(*U) = 1;
   AtkProb(*U) = 100;
  UpkeepCost(*U) = 100;
}
int main(){
	UnitList L;
	ul_infotype X;
	POINT U;
	ul_address P;
	int opsi=1;
	UL_CreateEmpty(&L);
	printf(" 0. Exit\n 1. IsEmpty \n 2.InsVFirst \n 3. InsVLast \n 4. UL_DelVFirst\n 5.UL_DelVLast \n 6. UL_DelP \n 7. NbElmt \n 8. PrintList \n 9. UL_DelAll\n");
	while(opsi!=0){
		scanf("%d",&opsi);
		switch(opsi){
			case 0 : 
				printf("ExitProgram....");
			break;
			case 1 : 
				if(UL_IsEmpty(L)){
					printf("List is empty\n");
				}else{
					printf("List not empty\n");
				}
			break;
			
			case 2:
				printf("Masukkan absis & ordinat titik dummy : ");
				BacaPOINT(&U);
				initdummy(&X,U);
				UL_InsVFirst(&L,X);
				printf("UL_InsVFirst done\n");
			break;
			
			case 3:
				printf("Masukkan absis & ordinat titik dummy : ");
				BacaPOINT(&U);
				initdummy(&X,U);
				UL_InsVLast(&L,X);
				printf("UL_InsVLast done\n");
			break;
			
			case 4:
				UL_DelVFirst(&L,&X);
				printf("unit dengan posisi ");
				TulisPOINT(Loc((X)));
				printf(" telah dihapus dari List\n");
			break;
			
			case 5:
				UL_DelVLast(&L,&X);
				printf("unit dengan posisi ");
				TulisPOINT(Loc((X)));
				printf(" telah dihapus dari List\n");
			break;
			
			case 6:
				BacaPOINT(&U);
				printf("unit dengan posisi ");
				TulisPOINT(U);
				UL_DelP(&L,X);				
				printf(" telah dihapus dari List\n");
			break;
			
			case 7:
				printf("NbElmenet dalam list adalah %d \n",UL_NbElmt(L));
			break;
			
			case 8:
				P = UL_First(L);
				while(P!=Nil){
					TulisPOINT(Loc(UL_Info(P)));
					P = UL_Next(P);
				}
				printf("\n");
			break;
			
			case 9:
				UL_DelAll (&L);
				printf("List sudah dihapus semua \n");
			break;
		}
	}
	
	return 0;
}
