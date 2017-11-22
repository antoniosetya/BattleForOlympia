/* NIM/Nama : 13516002/Antonio Setya */
/* File : queue.c */
/* Implementasi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include "boolean.h"
#include "queue.h"

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q) {
/* Mengirim true jika Q kosong */
  return ((Head(Q) == NilQ) && (Tail(Q) == NilQ));
}

boolean IsFull (Queue Q) {
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
  return (NBElmtQueue(Q) == MaxQueueEl);
}

int NBElmtQueue (Queue Q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
  if (IsEmpty(Q)) {
    return 0;
  }
  else if (Tail(Q) < Head(Q)) {
    return ((MaxQueueEl + 1 + Tail(Q)) - Head(Q));
  }
  else {
    return (Tail(Q) + 1 - Head(Q));
  }
}

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q) {
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
  Head(*Q) = NilQ;
  Tail(*Q) = NilQ;
}

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infoQ X) {
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
      if (Tail(*Q) > MaxQueueEl) {
        Tail(*Q) = 1;
      }
      InfoTail(*Q) = X;
    }
  }
}

void Del (Queue * Q, infoQ * X) {
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
  *X = InfoHead(*Q);
  if (NBElmtQueue(*Q) == 1) {
    Head(*Q) = NilQ;
    Tail(*Q) = NilQ;
  }
  else {
    Head(*Q)++;
    if (Head(*Q) > MaxQueueEl) {
      Head(*Q) = 1;
    }
  }
}
