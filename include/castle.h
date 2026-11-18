#ifndef CASTLE_H
#define CASTLE_H

#include "tower.h"
#include "enums.h"


class Castle{
private:
Tower towers[4];

public:
Castle();
~Castle();
void init(double start_health , double power,int num_targets);
Tower & get_tower(REGION r);
REGION resolve_region(REGION r);
bool is_all_destroyed();
double get_total_damage(REGION r);
double get_health(REGION r);
};

#endif