//YA RASOUL-ALLAH

#ifndef BP_PROJECT_PHYSICS_H
#define BP_PROJECT_PHYSICS_H


void move_tanks(Tank *tank, bool yn);

void turn_tanks(Tank *tank, bool yn);

void fire(Tank *tank, bool yn);

short pingpong(Map *map, bool yn);

void save_game(Map *map, bool yn);

#endif //BP_PROJECT_PHYSICS_H
