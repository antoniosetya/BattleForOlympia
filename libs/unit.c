#include "unit.h"
#include <time.h>

float randomize(){
  srand(time(NULL));
  float r = (float)rand()/(float)RAND_MAX;
  return r;
}

void InitUnit (Unit *U, UTemplate Template, int Owner, POINT Loc) {
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
    Owner(*U) = Owner;

}
