#include "UnitList.h"
#include <stdio.h>
#include <time.h>

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

int main(UnitList *P1,UnitList *P2){
	//I.S. : AtkState(*P1) = True;
	//F.S : Unit *P1 menyerang Unit *P2,Unit *P2 membalas jika tipe serangan sama.
	//Unit P1 tidak dapat menyerang lagi dan kehabisan movement point
	
	/*Kamus Lokal*/
	int i,pilihan;
	Unit P_1 = First(*P1); //Current Unit = First Unit di List ????????
	Unit P_2 = First(*P2);
	UnitList P_fight;		//P_fight menyimpan daftar unit yang bisa diserang
	/*Algoritma*/
	/*Mendata Unit yang dapat diserang*/
	UL_CreateEmpty(&P_fight);
	while(P_2!=Nil){
		if(Panjang(Loc(P_1),Loc(P_2))==1){  //Jika ada unit bersebelahan,unit tersebut dimasukkan ke P_fight
			UL_InsVLast(*P_fight,P_2);
		}
	P_2 = Next(P_2);
	}
	
	P_2 = First(P_Fight);
	/*Menampilkan Unit yang dapat diserang*/
	for(i=1;i<=UL_NbElmt(P_fight);i++){ //Print daftar unit yang dapat diserang
		printf("%d. ",i);
		PrintUnitType(P_2);
		TulisPOINT(P_2);
		printf("| Health %d/%d |",HP(P_2),MaxHP(P_2));
		if(AttackType(P_1)==AttackType(P_2)||UnitType(P_2)=='K'){
			printf("Able to retaliates\n");
		}else{
			printf("Unable to retaliates\n");
		}
		/*printf("Hit Chance = %.2f \n");*///	Probability
	}
	/*Tahap untuk mulai menyerang*/
	printf("Select​ ​enemy​ ​you​ ​want​ ​to​ ​attack​:​ ​");
	scanf("%d",&pilihan);
	while(pilihan>UL_NbElmt(P_fight)||pilihan<0){
		printf("Choice doesn't Exist\nSelect​ ​enemy​ ​you​ ​want​ ​to​ ​attack​:​");
		scanf("%d",&pilihan);
	}
	P_2 = First(P_fight);
	for(i=1;i<pilihan;i++){
		P_2 = Next(P_2);
	}
	/*Serang-menyerang*/
	printf("P1");
	PrintUnitType(P_1);
	printf("attack P2");
	PrintUnitType(P_2);
	printf("!\n")
	HP(P_2) = HP(P_2) - Attack(P_1);
	printf("P2");
	PrintUnitType(P_2);
	printf("damaged by %d !\n",Attack(P_1));
	//Retalation jika tipe attack sama&&belum mati atau tipe unit king danbelum mati
	if(AttackType(P_1)==AttackType(P_2)&&HP(P_2)>0||UnitType(P2)=='K'&&HP(P_2)>0){
		printf("P2 ");
		PrintUnitType(P_2);
		printf("begin to retaliates\n ");
		HP(P_1) = HP(P_1) - Attack(P_2);
		printf("P1");
		PrintUnitType(P_1);
		printf("damaged by %d !\n",Attack(P_2));
		//Menampilkan pesan apabila ada unit yang mati
		if(HP(P_1)<0){
			printf("P2 ");
			PrintUnitType(P_1);
			printf("is Dead\n");
		}
	}else{
		if(HP(P_2)<0){
			printf("P2 ");
			PrintUnitType(P_2);
			printf("is Dead\n");
		}
	}
	//Unit P_1 kehabisan movement point dan kesempatan untuk menyerang
	Steps(P_1) = 0;
	AtkState(P_1) = false;
	//Jika yang mati adalah King,maka delete seluruh unit 
	if(HP(P_2)<0)&&UnitType(P_2)=='K'){
		UL_DelAll(*P2);
	}
	if(HP(P_1)<0)&&UnitType(P_1)=='K'){
		UL_DelAll(*P1);
	}
}
