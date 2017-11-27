/* NIM/Nama : 13516002/Antonio Setya */
/* Tanggal  : 30 Agustus 2017 */
/* File Driver untuk ADT Point
   Mungkin tidak semua fungsi dipanggil di driver ini.
   Hal ini karena beberapa fungsi yang dipanggil disini
   telah memanggil fungsi yang tidak dipanggil di driver ini */

#include "../boolean.h"
#include "../point.h"
#include <stdio.h>

void PrintBool(int i) {
  if (i) {
    printf("true");
  }
  else {
    printf("false");
  }
}

int main() {
  POINT P1, P2;
  float x, y, sudut;
  printf("Masukkan absis & ordinat titik pertama : ");
  BacaPOINT(&P1);
  printf("Masukkan absis & ordinat titik kedua : ");
  BacaPOINT(&P2);
  printf("\nRelasi dengan titik kedua...\n");
  printf("Titik 1 = Titik 2 ? : ");PrintBool(EQ(P1,P2));printf("\n");
  printf("Titik 1 != Titik 2 ? : ");PrintBool(NEQ(P1,P2));printf("\n");
  printf("Panjang garis titik pertama dan kedua : %.2f\n",Panjang(P1,P2));
  printf("\nKembali ke titik pertama...\n");
  printf("Jika digeser sekali sejajar sumbu X, titik menjadi : ");TulisPOINT(NextX(P1));
  printf("\n");
  printf("Jika digeser sekali sejajar sumbu Y, titik menjadi : ");TulisPOINT(NextY(P1));
  printf("\n");
  printf("Geser titik pertama sejauh (x y) : ");scanf("%f %f",&x,&y);
  printf("Hasil pergeseran : ");TulisPOINT(PlusDelta(P1,x,y));printf("\n");
  printf("Ini juga membuat titik digeser : ");
  Geser(&P1,x,y);
  TulisPOINT(P1);
  printf("\n");
  printf("\n");
  printf("Digeser ke sumbu X : ");
  GeserKeSbX(&P1);
  TulisPOINT(P1);
  printf("\n");
  printf("Digeser ke sumbu Y : ");
  GeserKeSbY(&P1);
  TulisPOINT(P1);
  printf("\n");
  return 0;
}
