/* NIM/Nama : 13516002/Antonio Setya */
/* Tanggal : 14 September 2017 */
/* Topik : ADT Matriks */
/* IMPLEMENTASI TYPE MATRIKS dengan indeks dan elemen integer */

#include "boolean.h"
#include "player.h"
#include "map.h"
#include "pcolor.h"
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
        printf("Map-generating failed at row %d!\n",i);
        AllocSuccess = false;
      }
      else {
        int j;
        for (j = 0;j <= NK; j++) {
          /* Initialize all map cells as empty */
          (*M).Mem[i][j].BData.Type = 'N';
          (*M).Mem[i][j].BData.owner = '0';
          POINT temp = MakePOINT(i,j);
          (*M).Mem[i][j].BData.pos = temp;
          (*M).Mem[i][j].CurUnit = Nil;
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
  printf("    ");
  for (j = 1;j <= NKol(M); j++) {
    printf(" %3d ",j);
  }
  printf("\n    ");
  for (j = 1;j <= NKol(M); j++) {
    printf("*****");
  }
  printf("\n");
  for (i = 1;i <= NBrs(M); i++) {
    printf("    ");
    for (j = 1;j <= NKol(M); j++) {
      if (Elmt(M,j,i).BData.Type != 'N') {
        if (Elmt(M,j,i).BData.owner != 0) {
          printf("* %s%c%s *",P_Data[Elmt(M,j,i).BData.owner].Color,Elmt(M,j,i).BData.Type,NORMAL);
        }
        else {
          printf("* %c *",Elmt(M,j,i).BData.Type);
        }
      }
      else {
        printf("*   *");
      }
    }
    printf("\n");
    printf("%3d ",i);
    for (j = 1;j <= NKol(M); j++) {
      if (Elmt(M,j,i).CurUnit != Nil) {
        printf("* %s%c%s *",P_Data[Owner(*Elmt(M,j,i).CurUnit)].Color,UnitType(*Elmt(M,j,i).CurUnit),NORMAL);
      }
      else {
        printf("*   *");
      }
    }
    printf("\n    ");
    for (j = 1;j <= NKol(M); j++) {
      printf("*   *");
    }
    printf("\n    ");
    for (j = 1;j <= NKol(M); j++) {
      printf("*****");
    }
    printf("\n");
  }
}

void UpdateBuildingOnMap (MAP *M, POINT pos, char type, int owner) {
/* I.S. M, pos terdefinisi, type dan owner sembarang
   F.S. Map pada posisi pos akan diupdate dengan value Type = type, owner = owner */
   if ((Absis(pos) > NKol(*M) || (Absis(pos) <= 0)) || ((Ordinat(pos) > NBrs(*M)) || (Ordinat(pos) <= 0))) {
     printf("Posisi yang ingin diubah diluar area map!\n");
   }
   else {
     Elmt(*M,Absis(pos),Ordinat(pos)).BData.Type = type;
     Elmt(*M,Absis(pos),Ordinat(pos)).BData.owner = owner;
     Elmt(*M,Absis(pos),Ordinat(pos)).BData.pos = pos;
   }
}
