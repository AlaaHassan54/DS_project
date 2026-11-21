#ifndef ENEMY_H
#define ENEMY_H

#include "enums.h"
#include "linkedlist/double_linkedlist.h"



class Tower;

class Enemy{
private:
int id;
int arrival_time ;
double original_health;
double curr_health;
double power;
int reload_period;
int first_shot_time;
int kill_time;
int next_action_time ;
int frozen_until;
REGION region;
int distance;
ENEMY_STATE state;
bool move_toggle;
void make_first_shot(int t);

public:
Enemy(int _id , int _arrival_time , double _health , double _power , int _reload_period , REGION _region);
virtual ~Enemy();
void act(int t , double_linkedlist<Enemy*>&active , Tower & tower);
virtual void do_action(int t ,double_linkedlist<Enemy*>&active , Tower & tower ) = 0;
virtual ENEMY_TYPE get_type() = 0;
void move(int t);
void take_damage(double damage_amount , int t);
void heal(double healing_amount);
void freeze(int t , int frozen_time);
bool is_frozen(int t);
bool is_half_health(int t);
bool is_alive();
bool can_act(int t);
int get_remaining_reload_time(int t);
double get_priority(int t);
int get_fd();
int get_kd();
int get_lt();
void set_region(REGION r);
void set_state(ENEMY_STATE s);


};
#endif