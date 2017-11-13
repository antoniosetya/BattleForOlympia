/* NIM / Nama : 13516002/Antonio Setya
   Tanggal : 26 Oktober 2017
   Topik : ADT List Linier */
/* ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

#include "boolean.h"
#include "UnitList.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (UnitList L) {
/* Mengirim true jika list kosong */
  return (First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (UnitList *L) {
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
  First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
  address P;
  P = (address) malloc (sizeof(ElmtUnitList));
  if (P != Nil) {
    Info(P) = X;
    Next(P) = Nil;
  }
  return P;
}

void Dealokasi (address *P) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
  if (P != Nil) {
    free(*P);
  }
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (UnitList L, infotype X) {
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
  address Pt = First(L);
  boolean found = false;
  while ((Pt != Nil) && !found) {
    found = (Info(Pt) == X);
    if (!found) {
      Pt = Next(Pt);
    }
  }
  return Pt;
}

boolean FSearch (UnitList L, address P) {
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
	address Pt = First(L);
	boolean found = false;
	while ((Pt != Nil) && !found) {
		found = (Pt == P);
		if (!found) {
			Pt = Next(Pt);
		}
	}
	return found;
}

address SearchPrec (UnitList L, infotype X) {
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
	address Pt = First(L);
	address Prev = Nil;
	boolean found = false;
	while ((Pt != Nil) && !found) {
		found = (Info(Pt) == X);
		if (!found) {
			Prev = Pt;
			Pt = Next(Pt);
		}
	}
	if (!found) {
		Prev = Nil;
	}
	return Prev;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (UnitList *L, infotype X) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
  address P = Alokasi(X);
  if (P != Nil) {
    if (IsEmpty(*L)) {
      First(*L) = P;
    }
    else {
      Next(P) = First(*L);
      First(*L) = P;
    }
  }
}

void InsVLast (UnitList *L, infotype X) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  address P = Alokasi(X);
  if (P != Nil) {
    if (IsEmpty(*L)) {
      First(*L) = P;
    }
    else {
      address Pt = First(*L);
      while(Next(Pt) != Nil) {
        Pt = Next(Pt);
      }
      Next(Pt) = P;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (UnitList *L, infotype *X) {
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
  if (!IsEmpty(*L)) {
    address Pt = First(*L);
    *X = Info(Pt);
    First(*L) = Next(Pt);
    Dealokasi(&Pt);
  }
}

void DelVLast (UnitList *L, infotype *X) {
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
  address Pt = First(*L);
  if (Next(Pt) == Nil) {
    DelVFirst(L,X);
  }
  else {
    while(Next(Next(Pt)) != Nil) {
      Pt = Next(Pt);
    }
    *X = Info(Next(Pt));
    Dealokasi(&Next(Pt));
    Next(Pt) = Nil;
  }
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (UnitList *L, address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
  Next(P) = First(*L);
  First(*L) = P;
}

void InsertAfter (UnitList *L, address P, address Prec) {
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void InsertLast (UnitList *L, address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
  address Pt = First(*L);
  if (Pt == Nil) {
    InsertFirst(L,P);
  }
  else {
    while (Next(Pt) != Nil) {
      Pt = Next(Pt);
    }
    Next(Pt) = P;
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (UnitList *L, address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
  *P = First(*L);
  First(*L) = Next(*P);
}

void DelP (UnitList *L, infotype X) {
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
  address Pt = First(*L);
  address PrevPt = Nil;
  boolean found = false;
  while ((Pt != Nil) && !found) {
    found = (Info(Pt) == X);
    if (!found) {
      PrevPt = Pt;
      Pt = Next(Pt);
    }
  }
  if (found) {
    if (PrevPt == Nil) {
      DelFirst(L,&Pt);
    }
    else {
      Next(PrevPt) = Next(Pt);
    }
    Dealokasi(&Pt);
  }
}

void DelLast (UnitList *L, address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
  address Pt = First(*L);
  address PrevPt = Nil;
  if (Pt == Nil) {
    DelFirst(L,P);
  }
  else {
    while (Next(Pt) != Nil) {
      PrevPt = Pt;
      Pt = Next(Pt);
    }
    if (PrevPt == Nil) {
      DelFirst(L,P);
    }
    else {
      Next(PrevPt) = Nil;
      *P = Pt;
    }
  }
}

void DelAfter (UnitList *L, address *Pdel, address Prec) {
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
  *Pdel = Next(Prec);
  Next(Prec) = Next(*Pdel);
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (UnitList L) {
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
  printf("[");
  address Pt = First(L);
  boolean isNotFirst = false;
  while(Pt != Nil) {
    if (isNotFirst) {
      printf(",");
    }
    printf("%d",Info(Pt));
    Pt = Next(Pt);
    isNotFirst = true;
  }
  printf("]");
}

int NbElmt (UnitList L) {
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
  int count = 0;
  address Pt = First(L);
  while (Pt != Nil) {
    count++;
    Pt = Next(Pt);
  }
  return count;
}

/****************** PROSES TERHADAP LIST ******************/
void DelAll (UnitList *L) {
/* Delete semua elemen list dan alamat elemen di-dealokasi */
	infotype temp;
	while (!IsEmpty(*L)) {
		DelVFirst(L,&temp);
	}
}