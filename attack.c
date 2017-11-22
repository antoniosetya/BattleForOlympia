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
	ul_address P_1 = Curr(*P1);			
	ul_address P_2 = First(*P2);
	UnitList P_fight;					//P_fight menyimpan daftar unit yang bisa diserang
	/*Algoritma*/
	/*Mendata Unit yang dapat diserang*/
	UL_CreateEmpty(&P_fight);
	while(P_2!=Nil){
		if(Panjang(Loc(Info(P_1)),Loc(Info(P_2)))==1){  //Jika ada unit bersebelahan,unit tersebut dimasukkan ke P_fight
			UL_InsVLast(&P_fight,Info(P_2));
		}
	P_2 = Next(P_2);
	}
	
	/*Menampilkan Unit yang dapat diserang*/
	P_2 = First(P_fight);
	if(UL_IsEmpty(P_fight)){								//Kasus jika tidak ada unit yang bisa diserang
		printf("There is no unit that you can attack \n");
	} 
	else{
		for(i=1;i<=UL_NbElmt(P_fight);i++){					 //Print daftar unit yang dapat diserang
			printf("%d. ",i);
			PrintUnitType(Info(P_2));
			TulisPOINT(Loc(Info(P_2)));
			printf("| Health %d/%d |",HP(Info(P_2)),MaxHP(Info(P_2)));
			if(AttackType(Info(P_1))==AttackType(Info(P_2))||UnitType(Info(P_2))=='K'){
				printf("Able to retaliates with %2.2f %%  \n",AtkProb(Info(P_2))*100);   
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
		
		P_2 = First(P_fight);			 //Mencari address unit yang ingin diserang
		for(i=1;i<=pilihan;i++){
			P_2 = Next(P_2);
		}
		/*Serang-menyerang*/
		printf("P1");
		PrintUnitType(Info(P_1));
		printf("attack P2");
		PrintUnitType(Info(P_2));
		printf("!\n");
		rndm = randomFloat();
		if(rndm<AtkProb(Info(P_1))){
			HP(Info(P_2)) = HP(Info(P_2)) - Attack(Info(P_1));
			printf("P2");
			PrintUnitType(Info(P_2));
			printf("damaged by %d !\n",Attack(Info(P_1)));
			
			printf("P2 ");  							//Menampilkan HP unit yang baru diserang
			PrintUnitType(Info(P_2));
			if(HP(Info(P_2))>0){
				printf("HP is %d/%d \n",HP(Info(P_2)),MaxHP(Info(P_2)));
			}else{
				printf("HP is 0/%d \n",MaxHP(Info(P_2)));
			}
		}
		else{
			printf("P1 ");
			PrintUnitType(Info(P_1));
			printf(" attack miss :( \n");
		}
		 
		//Retalation jika tipe attack sama&&belum mati atau tipe unit king danbelum mati
		if((AttackType(Info(P_1))==AttackType(Info(P_2))&&HP(Info(P_2))>0)||(UnitType(Info(P_2))=='K'&&HP(Info(P_2))>0)){
			printf("P2 ");
			PrintUnitType(Info(P_2));
			printf("begin to retaliates\n ");
			rndm = randomFloat();
			
			if(rndm<AtkProb(Info(P_2))){
				HP(Info(P_1)) = HP(Info(P_1)) - Attack(Info(P_2));
				printf("P1");
				PrintUnitType(Info(P_1));
				printf("damaged by %d !\n",Attack(Info(P_2)));
				
				printf("P1 ");  							//Menampilkan HP unit yang baru diretaliate
				PrintUnitType(Info(P_1));
				if(HP(Info(P_1))>0){
					printf("HP is %d/%d \n",HP(Info(P_1)),MaxHP(Info(P_1)));
				}else{
					printf("HP is 0/%d \n",MaxHP(Info(P_1)));
				}
			}
			else{
				printf("retalation P2 failed :\"\( \n");
			} 
		}
			
		//Menampilkan pesan apabila ada unit yang mati
		if(HP(Info(P_1))<0){
			printf("P1 ");
			PrintUnitType(Info(P_1));
			printf("is Dead\n");
			if(UnitType(Info(P_1))=='K'){
				UL_DelAll(P1);
			}else{
				UL_DelP(P1,Info(P_1));
			}
		 } else 
		 if(HP(Info(P_2))<0){  //Pakai else karena tidak mungkin keduanya Unit mati
			printf("P2 ");
			PrintUnitType(Info(P_2));
			printf("is Dead\n");
			UL_DelP (P2,Info(P_2));
			if(UnitType(Info(P_2))=='K'){
				UL_DelAll(P2);
			}else{
				UL_DelP (P2,Info(P_2));
			}
		 }
		
		//Unit Info(P_1)) kehabisan movement point dan kesempatan untuk menyerang
		Steps(Info(P_1)) = 0;
		AtkState(Info(P_1)) = false;
	} //tutup kurung dari line 55
}

