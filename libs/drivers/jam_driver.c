/* File: Driver untuk ADT JAM */

#include "../jam.h"
#include <stdio.h>

int main()
{
	JAM J1, J2;

	printf("TESTING JAM\n\n");
	printf("Jam Sekarang: ");
	// Mendapat jam sekarang
	GetCurrentJAM(&J1);
	// Menulis Jam sekarang
	TulisJAM(J1);
	printf("\n");
	// Konversi ke dalam detik
	printf("dalam detik: %ld\n", JAMToDetik(J1));
	printf("\nInput J2: ");
	// Membaca jam dari user
	BacaJAM(&J2);
	printf("Jam 2: ");
	TulisJAM(J2);
	printf("\n");
	// Menghitung durasi jam 1 dari jam skrg
	printf("Durasi dari Jam sekarang ke Jam 2: %ld\n", Durasi(J1,J2));
	printf("dalam Jam: ");
	TulisJAM(DetikToJAM(Durasi(J1,J2)));
	printf("\n");
	printf("Jam Sekarang + Jam2: ");
	TulisJAM(AddJAM(J1,J2));
	printf("\n");
   	return 0;
}