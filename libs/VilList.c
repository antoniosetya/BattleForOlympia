#include "boolean.h"
#include "VilList.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean VL_IsEmpty (VilList L) {
/* Mengirim true jika list kosong */
  return (VL_First(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void VL_CreateEmpty (VilList *L) {
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
  VL_First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
vl_address VL_Alokasi (infotype X) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
  vl_address P;
  P = (vl_address) malloc (sizeof(ElmtVilList));
  if (P != Nil) {
    VL_Info(P) = X;
    VL_Next(P) = Nil;
  }
  return P;
}

void VL_Dealokasi (vl_address *P) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
  if (P != Nil) {
    free(*P);
  }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void VL_InsVFirst (VilList *L, infotype X) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
  vl_address P = VL_Alokasi(X);
  if (P != Nil) {
    if (VL_IsEmpty(*L)) {
      VL_First(*L) = P;
    }
    else {
      VL_Next(P) = VL_First(*L);
      VL_First(*L) = P;
    }
  }
}

void VL_InsVLast (VilList *L, infotype X) {
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
  vl_address P = VL_Alokasi(X);
  if (P != Nil) {
    if (VL_IsEmpty(*L)) {
      VL_First(*L) = P;
    }
    else {
      vl_address Pt = VL_First(*L);
      while(VL_Next(Pt) != Nil) {
        Pt = VL_Next(Pt);
      }
      VL_Next(Pt) = P;
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void VL_DelVFirst (VilList *L, infotype *X) {
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
  if (!VL_IsEmpty(*L)) {
    vl_address Pt = VL_First(*L);
    *X = VL_Info(Pt);
    VL_First(*L) = VL_Next(Pt);
    VL_Dealokasi(&Pt);
  }
}

void VL_DelVLast (VilList *L, infotype *X) {
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
  vl_address Pt = VL_First(*L);
  if (VL_Next(Pt) == Nil) {
    VL_DelVFirst(L,X);
  }
  else {
    while(VL_Next(VL_Next(Pt)) != Nil) {
      Pt = VL_Next(Pt);
    }
    *X = VL_Info(VL_Next(Pt));
    VL_Dealokasi(&VL_Next(Pt));
    VL_Next(Pt) = Nil;
  }
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void VL_InsertFirst (VilList *L, vl_address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
  VL_Next(P) = VL_First(*L);
  VL_First(*L) = P;
}

void VL_InsertAfter (VilList *L, vl_address P, vl_address Prec) {
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
  VL_Next(P) = VL_Next(Prec);
  VL_Next(Prec) = P;
}

void VL_InsertLast (VilList *L, vl_address P) {
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
  vl_address Pt = VL_First(*L);
  if (Pt == Nil) {
    VL_InsertFirst(L,P);
  }
  else {
    while (VL_Next(Pt) != Nil) {
      Pt = VL_Next(Pt);
    }
    VL_Next(Pt) = P;
  }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void VL_DelFirst (VilList *L, vl_address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
  *P = VL_First(*L);
  VL_First(*L) = VL_Next(*P);
}

void VL_DelP (VilList *L, infotype X) {
/* I.S. Sembarang */
/* F.S. Jika ada unit dalam list yang berada di posisi P, dengan Info(P) = X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
  vl_address Pt = VL_First(*L);
  vl_address PrevPt = Nil;
  boolean found = false;
  while ((Pt != Nil) && !found) {
    found = EQ(VL_Info(Pt).pos,X.pos);
    if (!found) {
      PrevPt = Pt;
      Pt = VL_Next(Pt);
    }
  }
  if (found) {
    if (PrevPt == Nil) {
      VL_DelFirst(L,&Pt);
    }
    else {
      VL_Next(PrevPt) = VL_Next(Pt);
    }
    VL_Dealokasi(&Pt);
  }
}

void VL_DeleteP (VilList *L, infotype X, vl_address *P) {
/* Sama seperti VL_DelP, namun elemen list tidak di-dealokasi
   Jika tidak ada elemen list yang = X, *P = Nil */
  vl_address Pt = VL_First(*L);
  vl_address PrevPt = Nil;
  boolean found = false;
  while ((Pt != Nil) && !found) {
    found = EQ(VL_Info(Pt).pos,X.pos);
    if (!found) {
      PrevPt = Pt;
      Pt = VL_Next(Pt);
    }
  }
  if (found) {
    if (PrevPt == Nil) {
      VL_DelFirst(L,&Pt);
    }
    else {
      VL_Next(PrevPt) = VL_Next(Pt);
    }
    *P = Pt;
    VL_Next(*P) = Nil;
  }
}

void VL_DelLast (VilList *L, vl_address *P) {
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
  vl_address Pt = VL_First(*L);
  vl_address PrevPt = Nil;
  if (Pt == Nil) {
    VL_DelFirst(L,P);
  }
  else {
    while (VL_Next(Pt) != Nil) {
      PrevPt = Pt;
      Pt = VL_Next(Pt);
    }
    if (PrevPt == Nil) {
      VL_DelFirst(L,P);
    }
    else {
      VL_Next(PrevPt) = Nil;
      *P = Pt;
    }
  }
}

void VL_DelAfter (VilList *L, vl_address *Pdel, vl_address Prec) {
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus VL_Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
  *Pdel = VL_Next(Prec);
  VL_Next(Prec) = VL_Next(*Pdel);
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
/* void PrintInfo (VilList L) { */
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/*
} */

int VL_NbElmt (VilList L) {
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
  int count = 0;
  vl_address Pt = VL_First(L);
  while (Pt != Nil) {
    count++;
    Pt = VL_Next(Pt);
  }
  return count;
}

/****************** PROSES TERHADAP LIST ******************/
void VL_DelAll (VilList *L) {
/* Delete semua elemen list dan alamat elemen di-dealokasi */
	infotype temp;
	while (!VL_IsEmpty(*L)) {
		VL_DelVFirst(L,&temp);
	}
}
