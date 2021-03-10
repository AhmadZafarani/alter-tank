//YA HOSSEIN

#ifndef BP_PROJECT_LOGIC_H
#define BP_PROJECT_LOGIC_H


#include <stdbool.h>
#include "struct.h"

void death(Tank *tank, bool yn);

bool movement_collids_walls(Map *map, short a);

short isthere(Map *map);


#endif //BP_PROJECT_LOGIC_H
