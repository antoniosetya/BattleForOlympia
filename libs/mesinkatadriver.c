/* File: Driver untuk ADT Mesin Kata */

#include <stdio.h>
#include "mesinkata.h"

int main()
{
	Kata K, STRING;
	int bil;
	printf("Driver Mesinkata and mesinkar\n\n");
	printf("Reading Kata from mesinkatatest.txt...\n");
	STARTKATA("mesinkatatest.txt");
	while (!EndKata)
	{
		TulisKata(CKata);
		printf("\n");		
	    ADVKATA();
	}
	printf("\n");
    BacaKata(&K);
    CreateKata(&STRING, "hehe");
    if(IsKataSama(K,STRING))
    {
    	printf("String is hehe\n");
    }
    else
    {
    	printf("String is not hehe\n");
    }

    printf("\nTesting KataToInteger\n");
    printf("Input sebuah angka: ");
    BacaKata(&K);
    bil = KataToInteger(K);
    printf("Kata to int: %d\n", bil);
	return 0;
}