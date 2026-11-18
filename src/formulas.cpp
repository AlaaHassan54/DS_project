#include "formulas.h"
#include "config.h"
#include <algorithm>



double Formulas::fighter_damage(double enemy_power , int enemy_dis , bool is_half_health){
    int k = is_half_health? 0.5:1;
    return ((k*enemy_power)/enemy_dis);
}


double Formulas::ice_per_shot(double enemy_power , int enemy_dis , bool is_half_health){
    int k = is_half_health? 0.5:1;
    return std::min(((k*enemy_power)/enemy_dis) , config::ICE_THRESHOLD);
}


double Formulas::bullet_damage(double tower_power , int enemy_dis , ENEMY_TYPE enemy_type){
    int k = (enemy_type == HEALER)? 2:1;
    return tower_power/(k*enemy_dis);
}


int Formulas::freeze_duration(double tower_power , int enemy_dis){
   int steps = tower_power/enemy_dis;
   if(steps<1) steps = 1;
   if(steps>config::MAX_FREEZE) steps = config::MAX_FREEZE;
   return steps;
}


double Formulas::heal_amount(double healer_power , int distance_diff){
    return healer_power/(1+distance_diff);
}


double Formulas::target_priority(int enemy_dis , double enemy_power , int reload_remaining,bool is_frozen , ENEMY_TYPE enemy_type){
    return  config::W_DIS*(config::MIN_DISTANCE/enemy_dis)+
            config::W_POW*(std::min(enemy_power/config::POWER_REF,1.0))+
            config::W_READY*(1/(1+reload_remaining))+
            config::W_TYPE*(enemy_type == HEALER)-
            config::W_FROZEN*(is_frozen);
            
}

