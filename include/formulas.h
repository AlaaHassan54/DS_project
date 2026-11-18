#ifndef FORMULAS_H
#define FORMULAS_H

#include "enums.h"

class Formulas{
public:

static double fighter_damage(double enemy_power , int enemy_dis , bool is_half_health);
static double ice_per_shot(double enemy_power , int enemy_dis , bool is_half_health);
static double bullet_damage(double tower_power , int enemy_dis , ENEMY_TYPE enemy_type);
static int freeze_duration(double tower_power , int enemy_dis);
static double heal_amount(double healer_power , int distance_diff);
static double target_priority(int enemy_dis , double enemy_power , int reload_remaining,bool is_frozen , ENEMY_TYPE enemy_type);

};

#endif