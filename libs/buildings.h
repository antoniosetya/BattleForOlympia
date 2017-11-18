#ifndef _BUILDING_H
#define _BUILDING_H

#include "point.h"

/* B_Data : represent a building stats on a map */
typedef struct {
    char Type; // Either T : Tower, C : Castle, V : Village, N : Normal
    int owner; // Points to the owner of this building. If Type = N, owner = Nil
    POINT pos; // Location of this building
} B_Data;

#endif