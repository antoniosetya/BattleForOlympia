#include "libs\UnitList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
float randomFloat(){
     float r = (float)rand()/(float)RAND_MAX;
     return r;
}

void PrintUnitType(Unit P){
switch (UnitType(P)){
			case 'K' :
				printf("King ");
				break;
			case 'A' :
				printf("Archer ");
				break;
			case 'S' :
				printf("Swordsman ");
				break;
			case 'W' :
				printf("White Mage ");
				break;
		}
}

void attack(UnitList *P1,UnitList *P2){
	//I.S. : AtkState(*P1) = True;
	//F.S : Unit *P1 menyerang Unit *P2,Unit *P2 membalas jika tipe serangan sama.
	//Unit P1 tidak dapat menyerang lagi dan kehabisan movement point
	//Harusnya udah beres

	/*Kamus Lokal*/
	int i,pilihan;
	float rndm;
	srand(time(NULL)); 					//Untuk keperluan Seed Random
	ul_address P_1 = UL_Curr(*P1);
	ul_address P_2 = UL_First(*P2);
	UnitList P_fight;					//P_fight menyimpan daftar unit yang bisa diserang
	/*Algoritma*/
	/*Mendata Unit yang dapat diserang*/
	UL_CreateEmpty(&P_fight);
	while(P_2!=Nil){
		if(Panjang(Loc(UL_Info(P_1)),Loc(UL_Info(P_2)))==1){  //Jika ada unit bersebelahan,unit tersebut dimasukkan ke P_fight
			UL_InsVLast(&P_fight,UL_Info(P_2));
		}
	P_2 = UL_Next(P_2);
	}

	/*Menampilkan Unit yang dapat diserang*/
	P_2 = UL_First(P_fight);
	if(UL_IsEmpty(P_fight)){								//Kasus jika tidak ada unit yang bisa diserang
		printf("There is no unit that you can attack \n");
	}
	else{
		for(i=1;i<=UL_NbElmt(P_fight);i++){					 //Print daftar unit yang dapat diserang
			printf("%d. ",i);
			PrintUnitType(UL_Info(P_2));
			TulisPOINT(Loc(UL_Info(P_2)));
			printf("| Health %d/%d |",HP(UL_Info(P_2)),MaxHP(UL_Info(P_2)));
			if(AttackType(UL_Info(P_1))==AttackType(UL_Info(P_2))||UnitType(UL_Info(P_2))=='K'){
				printf("Able to retaliates with %2.2f %%  \n",AtkProb(UL_Info(P_2))*100);
			}else{
				printf("Unable to retaliates\n");
			}
		}

		/*Tahap untuk mulai menyerang*/
		printf("Select​ ​enemy​ ​you​ ​want​ ​to​ ​attack​:​ ​\n");
		scanf("%d",&pilihan);
		while(pilihan>UL_NbElmt(P_fight)||pilihan<0){
			printf("Choice doesn't Exist\nSelect​ ​enemy​ ​you​ ​want​ ​to​ ​attack​: ​");
			scanf("%d",&pilihan);
		}

		P_2 = UL_First(P_fight);			 //Mencari address unit yang ingin diserang
		for(i=1;i<=pilihan;i++){
			P_2 = UL_Next(P_2);
		}
		/*Serang-menyerang*/
		printf("P1");
		PrintUnitType(UL_Info(P_1));
		printf("attack P2");
		PrintUnitType(UL_Info(P_2));
		printf("!\n");
		rndm = randomFloat();
		if(rndm<AtkProb(UL_Info(P_1))){
			HP(UL_Info(P_2)) = HP(UL_Info(P_2)) - Attack(UL_Info(P_1));
			printf("P2");
			PrintUnitType(UL_Info(P_2));
			printf("damaged by %d !\n",Attack(UL_Info(P_1)));

			printf("P2 ");  							//Menampilkan HP unit yang baru diserang
			PrintUnitType(UL_Info(P_2));
			if(HP(UL_Info(P_2))>0){
				printf("HP is %d/%d \n",HP(UL_Info(P_2)),MaxHP(UL_Info(P_2)));
			}else{
				printf("HP is 0/%d \n",MaxHP(UL_Info(P_2)));
			}
		}
		else{
			printf("P1 ");
			PrintUnitType(UL_Info(P_1));
			printf(" attack miss :( \n");
		}

		//Retalation jika tipe attack sama&&belum mati atau tipe unit king danbelum mati
		if((AttackType(UL_Info(P_1))==AttackType(UL_Info(P_2))&&HP(UL_Info(P_2))>0)||(UnitType(UL_Info(P_2))=='K'&&HP(UL_Info(P_2))>0)){
			printf("P2 ");
			PrintUnitType(UL_Info(P_2));
			printf("begin to retaliates\n ");
			rndm = randomFloat();

			if(rndm<AtkProb(UL_Info(P_2))){
				HP(UL_Info(P_1)) = HP(UL_Info(P_1)) - Attack(UL_Info(P_2));
				printf("P1");
				PrintUnitType(UL_Info(P_1));
				printf("damaged by %d !\n",Attack(UL_Info(P_2)));

				printf("P1 ");  							//Menampilkan HP unit yang baru diretaliate
				PrintUnitType(UL_Info(P_1));
				if(HP(UL_Info(P_1))>0){
					printf("HP is %d/%d \n",HP(UL_Info(P_1)),MaxHP(UL_Info(P_1)));
				}else{
					printf("HP is 0/%d \n",MaxHP(UL_Info(P_1)));
				}
			}
			else{
				printf("retalation P2 failed :\"\( \n");
			}
		}

		//Menampilkan pesan apabila ada unit yang mati
		if(HP(UL_Info(P_1))<0){
			printf("P1 ");
			PrintUnitType(UL_Info(P_1));
			printf("is Dead\n");
			if(UnitType(UL_Info(P_1))=='K'){
				UL_DelAll(P1);
			}else{
				UL_DelP(P1,UL_Info(P_1));
			}
		 } else
		 if(HP(UL_Info(P_2))<0){  //Pakai else karena tidak mungkin keduanya Unit mati
			printf("P2 ");
			PrintUnitType(UL_Info(P_2));
			printf("is Dead\n");
			UL_DelP (P2,UL_Info(P_2));
			if(UnitType(UL_Info(P_2))=='K'){
				UL_DelAll(P2);
			}else{
				UL_DelP (P2,UL_Info(P_2));
			}
		 }

		//Unit Info(P_1)) kehabisan movement point dan kesempatan untuk menyerang
		Steps(UL_Info(P_1)) = 0;
		AtkState(UL_Info(P_1)) = false;
	} //tutup kurung dari line 55
}
