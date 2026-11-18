#include "enemy/enemy.h"
#include "formulas.h"
#include "config.h"

//implement all these functionality (by Wafaa)


Enemy::Enemy(int _id , int _arrival_time , double _health , double _power , int _reload_period , REGION _region){



}


Enemy::~Enemy(){



}




void Enemy::act(int t , double_linkedlist<Enemy*>&active , Tower & tower){




}



void Enemy::move(int t){



}



void Enemy::take_damage(double damage_amount , int t){

}




void Enemy::heal(double healing_amount){

}



void Enemy::freeze(int t , int frozen_time){



}


bool Enemy::is_frozen(int t){


}


bool Enemy::is_half_health(int t){



}


bool Enemy::is_alive(){



}


bool Enemy::can_act(int t){



}


int Enemy::get_remaining_reload_time(int t){



}

double Enemy::get_priority(int t){


}


int Enemy::get_fd(){



}


int Enemy::get_kd(){



}
int Enemy::get_lt(){




}


void Enemy::set_region(REGION r){



}


void Enemy::set_state(ENEMY_STATE s){



}