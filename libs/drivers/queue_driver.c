/*  Driver ADT Queue */

#include "../boolean.h"
#include "../queue.h"
#include <stdio.h>

int main () {
	Queue antrian;
	CreateEmptyQueue(&antrian);
	char com;
	int elmnow, n;
	/* Input 1 untuk menambah elemen, 2 untuk menghapus elemen
	   Input 1 disertai dengan elemen yang ingin ditambah. Contoh : 1 3
	   Input 0 untuk mengakhiri program */
	do {
		scanf("%c",&com);
		if (com == '1') {
			scanf("%d",&elmnow);
			if (IsQueueFull(antrian)) {
				printf("Queue penuh\n");
			}
			else {
				Add(&antrian,elmnow);
			}
		}
		else if (com == '2') {
			if (IsQueueEmpty(antrian)) {
				printf("Queue kosong\n");
			}
			else {
				Del(&antrian,&elmnow);
				printf("%d\n",elmnow);
			}
		}
	}
	while (com != '0');
	printf("Jumlah antrian tersisa : %d\n",NBElmtQueue(antrian));
	return 0;
}
