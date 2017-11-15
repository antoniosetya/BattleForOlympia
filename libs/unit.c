#include "structs.h"
#include "unit.h"

void InitUnit (Unit Template, Player *P, POINT Loc) {
/* Initialize a new unit for a player based on a template */
    Unit U; // = Alokasi();
    UnitType(U) = UnitType(Template);
    MaxHP(U) = MaxHP(Template);
    HP(U) = MaxHP(U);
    Attack(U) = Attack(Template);
    AttackType(U) = AttackType(Template);
    MaxSteps(U) = MaxSteps(Template);
    Steps(U) = 0;
    AtkState(U) = false;
    Loc(U) = Loc;
    // UNIMPLEMENTED - Adds the unit into the list of units of the player */
}