#include "structs.h"
#include "pcolor.h"

void InitPlayer(Player *P,int PN) {
/* Initialize starting values of a player */
    Gold(*P) = 50;
    Income(*P) = 0;
    Upkeep(*P) = 0;
    switch(PN) {
        case 1:
            Color(*P) = RED;
            break;
        case 2:
            Color(*P) = BLUE;
            break;
        case 3:
            Color(*P) = MAGENTA;
            break;
        case 4:
            Color(*P) = CYAN;
            break;
    }
}

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