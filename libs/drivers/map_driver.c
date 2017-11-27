#include "../map.h"
#include <stdio.h>

int main(){
	MAP Map_Data,Map_Hsl;
	int row, col;
	POINT P;
    boolean isValid;
    Unit CurrUnit;
    // Membuat Point 
    P = MakePOINT(1,2);
    // Menerima input dimensi peta
    do {
      printf("Input the map size (rows cols, separated by a space) : ");
      scanf("%d %d",&row,&col);
      isValid = (row >= 8) && (col >= 8);
      if (!isValid) printf("Map dimension is not valid! (minimum is 8x8)\n");
    }
	while (!isValid);

	// Inisialisasi Map
	InitMAP(row,col,&Map_Data);
	// Cek kevalidan suatu indeks dalam map
	printf("Is Idx Valid ? %d\n",IsIdxValid(Map_Data,1,1));
	// Akses baris dan kol pertama dan terakhir
	printf("GetFirstIdxBrs %d\n GetFirstIdxKol %d\n GetLastIdxBrs %d\n GetLastIdxKol %d\n" , GetFirstIdxBrs(Map_Data) ,GetFirstIdxKol(Map_Data),GetLastIdxBrs(Map_Data),GetLastIdxKol(Map_Data));
	// Prosedur duplikat map
	CopyMAP(Map_Data,&Map_Hsl);
	// Menggambar Peta untuk player 1
	DrawMAP(Map_Hsl,1);
	// Update Bangunan dan Unit dalam Peta
	UpdateBuildingOnMap(&Map_Data,P,'C',1);
	UpdateUnitOnMap(&Map_Data,P,&CurrUnit);
	return 0;
}