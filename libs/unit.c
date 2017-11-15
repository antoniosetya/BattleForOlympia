#include "structs.h"
#include "unit.h"

void InitUnit (Unit *U, Unit Template, POINT Loc) {
/* Initialize a new unit for a player based on a template */
    UnitType(*U) = UnitType(Template);
    MaxHP(*U) = MaxHP(Template);
    HP(*U) = MaxHP(*U);
    Attack(*U) = Attack(Template);
    AttackType(*U) = AttackType(Template);
    MaxSteps(*U) = MaxSteps(Template);
    Steps(*U) = 0;
    AtkState(*U) = false;
    Loc(*U) = Loc;
}