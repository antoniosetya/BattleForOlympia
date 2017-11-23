#ifndef UNIT_H
#define UNIT_H

#include "boolean.h"
#include "point.h"

/* Unit : structure to represent a unit stats */
typedef struct {
    char type; // Either K : King, A : Archer, S : Swordsman, W : White Mage
    int maxHP;
    int HP;
    int Atk;
    char AtkType;
    int def;
    int maxStep;
    int steps;
    boolean CanAttack;
    POINT pos;
    int owner;
    float AttackProbability; // between 0 and 1
} Unit;

/* You can use these selectors to access "Unit" data struct */
#define UnitType(P) (P).type
#define MaxHP(P) (P).maxHP
#define HP(P) (P).HP
#define Attack(P) (P).Atk
#define AttackType(P) (P).AtkType
#define Def(P) (P).def
#define MaxSteps(P) (P).maxStep
#define Steps(P) (P).steps
#define AtkState(P) (P).CanAttack
#define Loc(P) (P).pos
#define Owner(P) (P).owner
#define AtkProb(P) (P).AttackProbability
void InitUnit (Unit *U,Unit Template, int Owner, POINT Loc);
/* Initialize a new unit for a player based on a template */

void InitUnit (Unit *U, Unit Template, int Owner, POINT Loc);
/* Initialize a new unit for a player based on a template */

#include "unit.c"
#endif
