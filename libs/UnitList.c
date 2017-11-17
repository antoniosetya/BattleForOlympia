/* NIM / Nama : 13516002/Antonio Setya
   Tanggal : 26 Oktober 2017
   Topik : ADT List Linier */
/* ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */

#include "boolean.h"
#include "UnitList.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean UL_IsEmpty (UnitList L) {
/* Mengirim true jika list kosong */
  return (First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void UL_CreateEmpty (UnitList *L) {
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
  First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
ul_address UL_Alokasi (ul_infotype X) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
  ul_address P;
  P = (ul_address) malloc (sizeof(ElmtUnitList));
  if (P != Nil) {
    Info(P) = X;
    Next(P) = Nil;
  }
  return P;
}

void UL_Dealokasi (ul_address *P) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
  if (P != Nil) {
    free(*P);
  }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void UL_InsVFirst (UnitList *L, ul_infotype X) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
  ul_address P = UL_Alokasi(X);
  if (P != Nil) {
    if (UL_IsEmpty(*L)) {
      First(*L) = P;
    }
    else {
      Next(P) = First(*L);
      First(*L) = P;
    }
  }
}

void UL_InsVLast (UnitList *L, ul_infotype X) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  ul_address P = UL_Alokasi(X);
  if (P != Nil) {
    if (UL_IsEmpty(*L)) {
      First(*L) = P;
    }
    else {
      ul_address Pt = First(*L);
      while(Next(Pt) != Nil) {
        Pt = Next(Pt);
      }
      Next(Pt) = P;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void UL_DelVFirst (UnitList *L, ul_infotype *X) {
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
  if (!UL_IsEmpty(*L)) {
    ul_address Pt = First(*L);
    *X = Info(Pt);
    First(*L) = Next(Pt);
    UL_Dealokasi(&Pt);
  }
}

void UL_DelVLast (UnitList *L, ul_infotype *X) {
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
  ul_address Pt = First(*L);
  if (Next(Pt) == Nil) {
    UL_DelVFirst(L,X);
  }
  else {
    while(Next(Next(Pt)) != Nil) {
      Pt = Next(Pt);
    }
    *X = Info(Next(Pt));
    UL_Dealokasi(&Next(Pt));
    Next(Pt) = Nil;
  }
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void UL_InsertFirst (UnitList *L, ul_address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
  Next(P) = First(*L);
  First(*L) = P;
}

void UL_InsertAfter (UnitList *L, ul_address P, ul_address Prec) {
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void UL_InsertLast (UnitList *L, ul_address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
  ul_address Pt = First(*L);
  if (Pt == Nil) {
    UL_InsertFirst(L,P);
  }
  else {
    while (Next(Pt) != Nil) {
      Pt = Next(Pt);
    }
    Next(Pt) = P;
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void UL_DelFirst (UnitList *L, ul_address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
  *P = First(*L);
  First(*L) = Next(*P);
}

void UL_DelP (UnitList *L, ul_infotype X) {
/* I.S. Sembarang */
/* F.S. Jika ada unit dalam list yang berada di posisi P, dengan Info(P) = X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
  ul_address Pt = First(*L);
  ul_address PrevPt = Nil;
  boolean found = false;
  while ((Pt != Nil) && !found) {
    found = EQ(Loc(Info(Pt)),Loc(X));
    if (!found) {
      PrevPt = Pt;
      Pt = Next(Pt);
    }
  }
  if (found) {
    if (PrevPt == Nil) {
      UL_DelFirst(L,&Pt);
    }
    else {
      Next(PrevPt) = Next(Pt);
    }
    UL_Dealokasi(&Pt);
  }
}

void UL_DelLast (UnitList *L, ul_address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
  ul_address Pt = First(*L);
  ul_address PrevPt = Nil;
  if (Pt == Nil) {
    UL_DelFirst(L,P);
  }
  else {
    while (Next(Pt) != Nil) {
      PrevPt = Pt;
      Pt = Next(Pt);
    }
    if (PrevPt == Nil) {
      UL_DelFirst(L,P);
    }
    else {
      Next(PrevPt) = Nil;
      *P = Pt;
    }
  }
}

void UL_DelAfter (UnitList *L, ul_address *Pdel, ul_address Prec) {
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
  *Pdel = Next(Prec);
  Next(Prec) = Next(*Pdel);
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
/* void PrintInfo (UnitList L) { */
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/*
} */

int UL_NbElmt (UnitList L) {
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
  int count = 0;
  ul_address Pt = First(L);
  while (Pt != Nil) {
    count++;
    Pt = Next(Pt);
  }
  return count;
}

/****************** PROSES TERHADAP LIST ******************/
void UL_DelAll (UnitList *L) {
/* Delete semua elemen list dan alamat elemen di-dealokasi */
	ul_infotype temp;
	while (!UL_IsEmpty(*L)) {
		UL_DelVFirst(L,&temp);
	}
}