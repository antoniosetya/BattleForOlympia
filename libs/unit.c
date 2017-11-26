#include "unit.h"
#include <stdlib.h>
#include <time.h>

float randomize(){
  float r = (float)rand()/(float)RAND_MAX;
  return r;
}

void InitUnit (Unit *U, UTemplate Template, int Owner, POINT Loc) {
/* Initialize a new unit for a player based on a template */
  UnitType(*U) = TemplateType(Template);
  MaxHP(*U) = TemplateHP(Template);
  HP(*U) = MaxHP(*U);
  Attack(*U) = TemplateAtk(Template);
  AttackType(*U) = TemplateAtkType(Template);
  Def(*U) = TemplateDef(Template);
  MaxSteps(*U) = TemplateSteps(Template);
  Steps(*U) = MaxSteps(*U);
  AtkState(*U) = true;
  Loc(*U) = Loc;
  Owner(*U) = Owner;
  float Prob;
  if (UnitType(*U) == 'K') {
    Prob = 0.9;
  }
  else {
    srand(time(NULL));
    do {
      Prob = randomize();
    }
    while ((Prob < 0.7) || (Prob > 0.9));
  }
  AtkProb(*U) = Prob;
  UpkeepCost(*U) = TemplateUpkeepCost(Template);
}

void PrintUnitType(Unit U){
/* I.S. Sembarang Unit U terdefinisi*/
/* F.S. Print tipe Unit U berdasarkan singkatannya*/
	switch (UnitType(U)){
		case 'K' : printf("King ");			break;
		case 'A' : printf("Archer ");		break;
		case 'S' : printf("Swordsman ");	break;
		case 'W' : printf("White Mage ");	break;
	}
}
