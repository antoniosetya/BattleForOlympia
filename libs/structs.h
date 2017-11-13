#ifndef _STRUCTS_h
#define _STRUCTS_h

#include "boolean.h"
#include "point.h"
#include "pcolor.h"
#include "UnitList.h"

/* Unit : structure to represent a unit stats */
typedef struct {
    char type; // Either K : King, A : Archer, S : Swordsman, W : White Mage
    int maxHP;
    int HP;
    int Atk;
    char AtkType;
    int maxStep;
    int steps;
    boolean CanAttack;
    POINT pos;
} Unit;

/* You can use these selectors to access "Unit" data struct */
#define UnitType(P) (P).type
#define MaxHP(P) (P).maxHP
#define HP(P) (P).HP
#define Attack(P) (P).Atk
#define AttackType(P) (P).AtkType
#define MaxSteps(P) (P).maxStep
#define Steps(P) (P).steps
#define AtkState(P) (P).CanAttack
#define Loc(P) (P).pos

/* Player : structure to represent a player stats */
typedef struct {
    int Gold; // Amount of gold of a player
    UnitList Units;
    /* VilList Villages */
    int Income; // Amount of income per turn
    int Upkeep; // Cost of having several units
    char *Color; // Color code of this player
} Player;

/* You can use these selectors to access "Player" data struct */
#define Gold(P) (P).Gold
#define Income(P) (P).Income
#define Upkeep(P) (P).Upkeep

/* B_Data : represent a building stats on a map */
typedef struct {
    char Type; // Either T : Tower, C : Castle, V : Village, N : Normal
    int Player; // Owner of this building. If Type = N, Player = 0
} B_Data;

/* Cell : represent a cell of a map */
typedef struct {
    B_Data BData; // Available building on this cell
    Unit CurUnit; // Unit on this cell
} MapCell;

/* *** PLAYER DATA STRUCT GROUP *** */
void InitPlayer(Player *P, int PN);
/* Initialize starting values of a player. 
   PN (Player number, 1 <= PN <= 4) is used to assign a color to that player. */

/* *** UNIT DATA STRUCT GROUP *** */
void InitUnit (Unit *U,Unit Template, Player *P);
/* Initialize a new unit for a player based on a template */

#endif