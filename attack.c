#include "libs/UnitList.h"
#include <stdio.h>
#include "libs/map.h"
#include "libs/player.h"
#include <stdlib.h>
#include <time.h>

Player P_Data[3];

void initRandom() {
  srand(time(NULL));
}

float randomFloat(){
     float r = (float)rand()/(float)RAND_MAX;
     return r;
}

int attack(MAP *Map_Data, UnitList *P1,UnitList *P2){
	/* I.S. : AtkState(*P1) = True;
	   F.S : Unit *P1 menyerang Unit *P2, Unit *P2 membalas jika tipe serangan sama.
	   Unit P1 tidak dapat menyerang lagi dan kehabisan movement point.
     Dalam kondisi normal, fungsi akan mengembalikan nilai 0;
     Jika pemanggilan fungsi menyebabkan salah satu King dari pemain mati, fungsi
     akan mengembalikan nomor pemain. */

	/*Kamus Lokal*/
	int i, pilihan, winFlag;
  int NeffP_fight;
  winFlag = 0;
	float rndm;
	initRandom(); 					//Untuk keperluan Seed Random
	ul_address P_1 = UL_Curr(*P1);
	ul_address P_2 = UL_First(*P2);
  ul_address P_fight[5]; // Menampung sementara alamat unit yang bisa diserang
	/*Algoritma*/
	/*Mendata Unit yang dapat diserang*/
  i = 1;
	while(P_2 != Nil){
		if(Panjang(Loc(UL_Info(P_1)),Loc(UL_Info(P_2)))==1){  //Jika ada unit bersebelahan,unit tersebut dimasukkan ke P_fight
			P_fight[i] = P_2;
      i++;
		}
	  P_2 = UL_Next(P_2);
	}
  NeffP_fight = i-1;
	/*Menampilkan Unit yang dapat diserang*/
	if(NeffP_fight == 0){								//Kasus jika tidak ada unit yang bisa diserang
		printf("There is no unit that you can attack \n");
	}
	else{
		for (i = 1;i <= NeffP_fight; i++){					 //Print daftar unit yang dapat diserang
			printf("%d. ",i);
			PrintUnitType(UL_Info(P_fight[i]));
			TulisPOINT(Loc(UL_Info(P_fight[i])));
			printf("| Health %d/%d | ",HP(UL_Info(P_fight[i])),MaxHP(UL_Info(P_fight[i])));
			if(AttackType(UL_Info(P_1))==AttackType(UL_Info(P_fight[i]))||UnitType(UL_Info(P_fight[i]))=='K'){
				printf("Able to retaliates with %2.2f %%  \n",AtkProb(UL_Info(P_fight[i]))*100);
			}else{
				printf("Unable to retaliates\n");
			}
		}

		/*Tahap untuk mulai menyerang*/
		printf("Select​ ​enemy​ ​you​ ​want​ ​to​ ​attack​:​ ​\n");
		scanf("%d",&pilihan);
		while((pilihan > NeffP_fight) || (pilihan < 0)){
			printf("Choice doesn't Exist\nSelect​ ​enemy​ ​you​ ​want​ ​to​ ​attack​: ​");
			scanf("%d",&pilihan);
		}

		/*Serang-menyerang*/
		printf("P%d's ",Owner(UL_Info(P_1)));
		PrintUnitType(UL_Info(P_1));
		printf("attack P%d's ",Owner(UL_Info(P_fight[pilihan])));
		PrintUnitType(UL_Info(P_fight[pilihan]));
		printf("!\n");
		rndm = randomFloat();
		if(rndm < AtkProb(UL_Info(P_1))){
			HP(UL_Info(P_fight[pilihan])) = HP(UL_Info(P_fight[pilihan])) - Attack(UL_Info(P_1));
			printf("P%d's ",Owner(UL_Info(P_fight[pilihan])));
			PrintUnitType(UL_Info(P_fight[pilihan]));
			printf("damaged by %d !\n",Attack(UL_Info(P_1)));

			printf("P%d's ",Owner(UL_Info(P_fight[pilihan])));  							//Menampilkan HP unit yang baru diserang
			PrintUnitType(UL_Info(P_fight[pilihan]));
			if(HP(UL_Info(P_fight[pilihan]))>0){
				printf(" HP is %d/%d \n",HP(UL_Info(P_fight[pilihan])),MaxHP(UL_Info(P_fight[pilihan])));
			}else{
				printf(" HP is 0/%d \n",MaxHP(UL_Info(P_fight[pilihan])));
			}
		}
		else{
			printf("P%d's ",Owner(UL_Info(P_1)));
			PrintUnitType(UL_Info(P_1));
			printf(" attack miss :( \n");
		}

		//Retalation jika tipe attack sama&&belum mati atau tipe unit king danbelum mati
		if((AttackType(UL_Info(P_1))==AttackType(UL_Info(P_fight[pilihan])) && HP(UL_Info(P_fight[pilihan])) > 0)|| (UnitType(UL_Info(P_fight[pilihan]))=='K' && HP(UL_Info(P_fight[pilihan]))>0)){
			printf("P%d's ",Owner(UL_Info(P_fight[pilihan])));
			PrintUnitType(UL_Info(P_fight[pilihan]));
			printf("begin to retaliates\n ");
			rndm = randomFloat();

			if(rndm<AtkProb(UL_Info(P_fight[pilihan]))){
				HP(UL_Info(P_1)) = HP(UL_Info(P_1)) - Attack(UL_Info(P_fight[pilihan]));
				printf("P%d's ",Owner(UL_Info(P_1)));
				PrintUnitType(UL_Info(P_1));
				printf("damaged by %d !\n",Attack(UL_Info(P_fight[pilihan])));

				printf("P%d's ",Owner(UL_Info(P_1)));  							//Menampilkan HP unit yang baru diretaliate
				PrintUnitType(UL_Info(P_1));
				if(HP(UL_Info(P_1))>0){
					printf("HP is %d/%d \n",HP(UL_Info(P_1)),MaxHP(UL_Info(P_1)));
				}else{
					printf("HP is 0/%d \n",MaxHP(UL_Info(P_1)));
				}
			}
			else{
				printf("Retaliation failed :\"\( \n");
			}
		}

		//Menampilkan pesan apabila ada unit yang mati
		if(HP(UL_Info(P_1)) <= 0){
			printf("P%d's ",Owner(UL_Info(P_1)));
			PrintUnitType(UL_Info(P_1));
			printf("is Dead\n");
			if(UnitType(UL_Info(P_1)) == 'K'){
        winFlag = Owner(UL_Info(P_fight[pilihan]));
				UL_DelAll(P1);
			}else{
        UpdateUnitOnMap(Map_Data,Loc(UL_Info(P_1)),Nil);
        // Automatically chooses the next available unit
        if (UL_Next(P_1) == Nil) {
          UL_Curr(*P1) = UL_First(*P1);
        }
        else {
          UL_Curr(*P1) = UL_Next(P_1);
        }
        Upkeep(P_Data[Owner(UL_Info(P_1))])-=UpkeepCost(UL_Info(P_1));
				UL_DelP(P1,UL_Info(P_1));
			}
      P_1 = Nil;
     } else
		 if (HP(UL_Info(P_fight[pilihan])) <= 0) {  //Pakai else karena tidak mungkin keduanya Unit mati
			printf("P%d's ",Owner(UL_Info(P_fight[pilihan])));
			PrintUnitType(UL_Info(P_fight[pilihan]));
			printf("is Dead\n");
			if(UnitType(UL_Info(P_fight[pilihan])) == 'K'){
        winFlag = Owner(UL_Info(P_1));
				UL_DelAll(P2);
			}else{
        UpdateUnitOnMap(Map_Data,Loc(UL_Info(P_fight[pilihan])),Nil);
        // Automatically choose next unit if attacked unit is the current unit of the opposing
        if (P_fight[pilihan] == UL_Curr(*P2)) {
          if (UL_Next(P_fight[pilihan]) == Nil) {
            UL_Curr(*P2) = UL_First(*P2);
          }
          else {
            UL_Curr(*P2) = UL_Next(P_fight[pilihan]);
          }
        }
        Upkeep(P_Data[Owner(UL_Info(P_fight[pilihan]))])-=UpkeepCost(UL_Info(P_fight[pilihan]));
        UL_DelP (P2,UL_Info(P_fight[pilihan]));
			}
		 }

		//Unit Info(P_1)) kehabisan movement point dan kesempatan untuk menyerang
    if (P_1 != Nil) {
      Steps(UL_Info(P_1)) = 0;
  		AtkState(UL_Info(P_1)) = false;
    }
	} //tutup kurung dari line 55
  return winFlag;
}
