/* 	Driver ADT Stack (utama) + ADT Point */
	
#include "../point.h"
#include "../stackt.h"
#include <stdio.h>
#include <math.h>

int main() {
	Stack S;
	POINT temp;
	char com;
	CreateEmptyStack(&S);
	printf("Input 1 untuk push elemen, 2 untuk pop elemen\n");
	printf("Input 1 disertai dengan elemen yang ingin ditambah. Contoh : 1 5 6\n");
	printf("Input 0 untuk mengakhiri program\n");
	do {
		scanf("%c",&com);
		if (com == '1') {
			BacaPOINT(&temp);
			if (IsStackFull(S)) {
				printf("Stack penuh\n");
			}
			else {
				Push(&S,temp);
			}
		}
		else if (com == '2') {
			if (IsStackEmpty(S)) {
				printf("Stack kosong\n");
			}
			else {
				Pop(&S,&temp);
				TulisPOINT(temp);printf("\n");
			}
		}
	}
	while(com != '0');
	if (!IsStackEmpty(S)) {
		printf("Elemen tersisa dalam stack : \n");
		do {
			Pop(&S,&temp);
			TulisPOINT(temp);printf("\n");
		}
		while (!IsStackEmpty(S));
	}
	else {
		printf("Stack habis\n");
	}
}