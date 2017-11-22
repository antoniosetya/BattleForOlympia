/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#ifndef MATRIKS_H
#define MATRIKS_H

#include "boolean.h"
#include "player.h"
#include "unit.h"
#include "buildings.h"
#include <stdlib.h>

#define Nil NULL

/* Cell : represent a cell of a map */
typedef struct {
    B_Data BData; // Available building on this cell
    Unit *CurUnit; // Unit on this cell. CurUnit == Nil means there are no unit on this cell
} MapCell;

typedef int indeks; /* indeks baris, kolom */
typedef MapCell ElType;
typedef struct {
	ElType **Mem;
    int MaxBrs; // banyaknya baris pada map
    int MaxKol; // banyaknya kolom pada map
} MAP;
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void InitMAP (int NB, int NK, MAP * M);
/* Membentuk sebuah MAP (Matriks) "kosong" yang siap diisi berukuran NB x NK */
/* I.S. NB dan NK >= 0 */
/* F.S. MAP M dialokasi dengan definisi di atas */

/* *** Selektor *** */
#define NBrs(M) (M).MaxBrs
#define NKol(M) (M).MaxKol
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

void DealokMap(MAP *M);
/* Membebaskan M dan mengembalikan memori ke sistem */

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (MAP M, int i, int j);
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MAP M);
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MAP M);
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MAP M);
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MAP M);
/* Mengirimkan indeks kolom terbesar M */

/* ********** Assignment  MATRIKS ********** */
void CopyMAP (MAP MIn, MAP * MHsl);
/* Melakukan assignment MHsl <- MIn */

void DrawMAP (MAP M);
/* I.S. M terdefinisi */
/* F.S. Tergambar M(i,j), dengan format cell :
    *****
    * K *
    * U *
    *   *
    *****
    K = Bangunan yang ada di cell map. Jika K = N (Normal), diprint kosong
    U = Unit yang ada dalam cell itu */

#include "map.c"
#endif
