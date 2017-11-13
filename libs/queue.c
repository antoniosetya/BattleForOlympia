/* NIM/Nama : 13516002/Antonio Setya */
/* File : queue.c */
/* Implementasi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include "boolean.h"
#include "queue.h"

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q) {
/* Mengirim true jika Q kosong */
  return ((Head(Q) == Nil) && (Tail(Q) == Nil));
}

boolean IsFull (Queue Q) {
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
  return (NBElmt(Q) == MaxEl);
}

int NBElmt (Queue Q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
  if (IsEmpty(Q)) {
    return 0;
  }
  else if (Tail(Q) < Head(Q)) {
    return ((MaxEl + 1 + Tail(Q)) - Head(Q));
  }
  else {
    return (Tail(Q) + 1 - Head(Q));
  }
}

/* *** Kreator *** */
void CreateEmpty (Queue * Q) {
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
  Head(*Q) = Nil;
  Tail(*Q) = Nil;
}

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X) {
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
  if (!IsFull(*Q)) {
    if (IsEmpty(*Q)) {
      Head(*Q)++;
      Tail(*Q)++;
      InfoTail(*Q) = X;
    }
    else {
      Tail(*Q)++;
      if (Tail(*Q) > MaxEl) {
        Tail(*Q) = 1;
      }
      InfoTail(*Q) = X;
    }
  }
}

void Del (Queue * Q, infotype * X) {
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
  *X = InfoHead(*Q);
  if (NBElmt(*Q) == 1) {
    Head(*Q) = Nil;
    Tail(*Q) = Nil;
  }
  else {
    Head(*Q)++;
    if (Head(*Q) > MaxEl) {
      Head(*Q) = 1;
    }
  }
}
