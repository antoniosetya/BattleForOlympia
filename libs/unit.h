#ifndef UNIT_H
#define UNIT_H

#include "boolean.h"
#include "point.h"
#include "structs.h"

/* Unit : structure to represent a unit stats */
typedef struct {
    char type; // Either K : King, A : Archer, S : Swordsman, W : White Mage, N : Nothing (N is used for map-drawing)
    int maxHP;
    int HP;
    int Atk;
    char AtkType;
    int maxStep;
    int steps;
    boolean CanAttack;
    POINT pos;
    Player *owner; // Points to the owner of this unit
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
#define Owner(P) (P).owner

void InitUnit (Unit *U,Unit Template, POINT Loc);
/* Initialize a new unit for a player based on a template */

#endif