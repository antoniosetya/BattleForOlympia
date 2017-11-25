#include "player.h"
#include "pcolor.h"
#include <stdlib.h>

void InitPlayer(Player *P,int PN) {
/* Initialize starting values of a player */
    Gold(*P) = 150;
    Income(*P) = 0;
    Upkeep(*P) = 0;
    UL_CreateEmpty(&Units(*P));
    VL_CreateEmpty(&Villages(*P));
    (*P).Color = (char *) malloc (10 * sizeof(char));
    switch(PN) {
        case 1:
            (*P).Color = MAGENTA;
            break;
        case 2:
            (*P).Color = BLUE;
            break;
        case 3:
            (*P).Color = CYAN;
            break;
        case 4:
            (*P).Color = YELLOW;
            break;
    }
}
