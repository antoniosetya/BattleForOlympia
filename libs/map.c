/* NIM/Nama : 13516002/Antonio Setya */
/* Tanggal : 14 September 2017 */
/* Topik : ADT Matriks */
/* IMPLEMENTASI TYPE MATRIKS dengan indeks dan elemen integer */

#include "boolean.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void InitMAP (int NB, int NK, MAP * M) {
/* Membentuk sebuah MAP (Matriks) "kosong" yang siap diisi berukuran NB x NK */
/* I.S. NB dan NK >= 0 */
/* F.S. MAP M dialokasi dengan definisi di atas. 
        Jika ada alokasi yang gagal, M = Nil */
  (*M).Mem = (ElType **) malloc ((NB + 1) * sizeof(ElType *));
  if ((*M).Mem != Nil) {
    NBrs(*M) = NB;
    int i;
    boolean AllocSuccess = true;
    for (i = 0;(i<= NBrs(*M)) && AllocSuccess;i++) {
      (*M).Mem[i] = (ElType *) malloc ((NK + 1) * sizeof(ElType));
      if ((*M).Mem[i] == Nil) {
        AllocSuccess = false;
      }
      else {
        // untuk sekarang, semua map diinisialisasi N;
        int j;
        for (j = 0;j <= NK; j++) {
          (*M).Mem[i][j].BData.Type = 'N';
        }
      }
    }
    if (AllocSuccess) {
      NKol(*M) = NK;
    }
    else {
      DealokMap(M);
      M = Nil;
    }
  }
}

void DealokMap(MAP *M) {
/* Membebaskan M dan mengembalikan memori ke sistem */
  free((*M).Mem);
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (MAP M, int i, int j) {
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
  return ((i >= 1) && (i <= NBrs(M)) && (j >= 1) & (j <= NKol(M)));
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MAP M) {
/* Mengirimkan indeks baris terkecil M */
  return 1;
}

indeks GetFirstIdxKol (MAP M) {
/* Mengirimkan indeks kolom terkecil M */
  return 1;
}

indeks GetLastIdxBrs (MAP M) {
/* Mengirimkan indeks baris terbesar M */
  return NBrs(M);
}

indeks GetLastIdxKol (MAP M) {
/* Mengirimkan indeks kolom terbesar M */
  return NKol(M);
}


void CopyMAP (MAP MIn, MAP * MHsl) {
// Melakukan assignment MHsl <- MIn
  InitMAP(NBrs(MIn),NKol(MIn),MHsl);
  int i, j;
  for (i = 0;i <= NBrs(*MHsl); i++) {
    for (j = 0;j <= NKol(*MHsl); j++) {
      Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
    }
  }
}

void DrawMAP (MAP M) {
/* I.S. M terdefinisi */
/* F.S. Tergambar M(i,j), dengan nomor kolom dan baris di pinggir map dan format setiap cell : 
    ***** 
    * K *
    * U *
    *   *
    ***** 
    K = Bangunan yang ada di cell map. Jika K = N (Normal), diprint kosong
    U = Unit yang ada dalam cell itu */
  int i, j;
  printf("  ");
  for (j = 1;j <= NKol(M); j++) {
    printf("  %d  ",j);
  }
  printf("\n  ");
  for (j = 1;j <= NKol(M); j++) {
    printf("*****");
  }
  printf("\n");
  for (i = 1;i <= NBrs(M); i++) {
    printf("  ");
    for (j = 1;j <= NKol(M); j++) {
      if (Elmt(M,i,j).BData.Type != 'N') {
        printf("* %c *",Elmt(M,i,j).BData.Type);
      }
      else {
        printf("*   *");
      }
    }
    printf("\n");
    printf("%d ",i);
    for (j = 1;j <= NKol(M); j++) {
      if (Elmt(M,i,j).CurUnit.type != 'N') {
        printf("* %c *",Elmt(M,i,j).CurUnit.type);
      }
      else {
        printf("*   *");
      }
    }
    printf("\n  ");
    for (j = 1;j <= NKol(M); j++) {
      printf("*   *");
    }
    printf("\n  ");
    for (j = 1;j <= NKol(M); j++) {
      printf("*****");
    }
    printf("\n");
  }
}