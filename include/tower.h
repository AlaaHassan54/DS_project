
#ifndef TOWER_H
#define TOWER_H

#include "enums.h"
#include "linkedlist/double_linkedlist.h"
#include "enemy/enemy.h"

class Tower{
private:
REGION region;
double start_health;
double curr_health;
double power;
double accumulated_ice;
int frozen_until;
int num_targets;
int total_shots;
int ice_shots;
double total_damage_taken;
Enemy** targets;

public:
Tower();
~Tower();
void init(REGION _region , double _start_health , double _power , int _num_targets);
void act(int t , double_linkedlist<Enemy*>& active);
int pick_targets(int t ,double_linkedlist<Enemy*>& active);
bool can_fire_ice(int t , const Enemy * enemy);
void fire_bullets(int t ,Enemy * enemy);
void fire_ice(int t ,Enemy * enemy);
void take_damage(double damage_amount);
void take_ice(double ice_amount , int t);
bool is_frozen(int t);
bool is_destroyed(int t);
REGION get_region();
double get_curr_health();
double get_start_health();
double get_power();
int get_num_targets();
double get_total_damage_taken();



};
#endif