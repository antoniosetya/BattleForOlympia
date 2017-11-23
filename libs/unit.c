#include "player.h"
#include "unit.h"

void InitUnit (Unit *U, Unit Template, int Owner, POINT Loc) {
/* Initialize a new unit for a player based on a template */
    UnitType(*U) = UnitType(Template);
    MaxHP(*U) = MaxHP(Template);
    HP(*U) = MaxHP(*U);
    Attack(*U) = Attack(Template);
    AttackType(*U) = AttackType(Template);
    Def(*U) = Def(Template);
    MaxSteps(*U) = MaxSteps(Template);
    Steps(*U) = 0;
    AtkState(*U) = false;
    Loc(*U) = Loc;
    Owner(*U) = Owner;
}