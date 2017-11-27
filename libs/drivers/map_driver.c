#include "../map.h"
#include <stdio.h>

int main(){
	MAP Map_Data,Map_Hsl;
	int row, col;
	POINT P;
    boolean isValid;
    Unit CurrUnit;
    P = MakePOINT(1,2);
    do {
      printf("Input the map size (rows cols, separated by a space) : ");
      scanf("%d %d",&row,&col);
      isValid = (row >= 8) && (col >= 8);
      if (!isValid) printf("Map dimension is not valid! (minimum is 8x8)\n");
    }
	while (!isValid);

	InitMAP(row,col,&Map_Data);
	printf("Is Idx Valid ? %d\n",IsIdxValid(Map_Data,1,1));
	printf("GetFirstIdxBrs %d\n GetFirstIdxKol %d\n GetLastIdxBrs %d\n GetLastIdxKol %d\n" , GetFirstIdxBrs(Map_Data) ,GetFirstIdxKol(Map_Data),GetLastIdxBrs(Map_Data),GetLastIdxKol(Map_Data));
	CopyMAP(Map_Data,&Map_Hsl);
	DrawMAP(Map_Hsl,1);
	UpdateBuildingOnMap(&Map_Data,P,'C',1);
	UpdateUnitOnMap(&Map_Data,P,&CurrUnit);
	return 0;
}