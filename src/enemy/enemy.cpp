#include "enemy/enemy.h"
#include "formulas.h"
#include "config.h"

//implement all these functionality (by Wafaa)


Enemy::Enemy(int _id , int _arrival_time , double _health , double _power , int _reload_period , REGION _region){
    id= _id;
    arrival_time = _arrival_time;
    original_health = _health;
    curr_health = _health;
    power = _power;
    reload_period = _reload_period;
    region = _region;

    first_shot_time = -1;
    kill_time = -1;
    next_action_time = _arrival_time;
    frozen_until = -1;
    distance = config::START_DISTANCE;
    state = INACTIVE;
    move_toggle = false;

}


// ---------- getters for other modules ----------

int Enemy::get_id(){ return id; }

int Enemy::get_arrival_time(){ return arrival_time; }

int Enemy::get_kill_time(){ return kill_time; }

double Enemy::get_power(){ return power; }

double Enemy::get_health(){ return curr_health; }

int Enemy::get_distance(){ return distance; }

REGION Enemy::get_region(){ return region; }

ENEMY_STATE Enemy::get_state(){ return state; }


Enemy::~Enemy(){
    //no dynamic memory allocation in Enemy
}

void Enemy::make_first_shot(int t){
    if (first_shot_time == -1)
        first_shot_time = t;
}

void Enemy::act(int t , double_linkedlist<Enemy*>&active , Tower & tower){
    if(state != ACTIVE)
        return;

    //to prevent enemy to take action till first shot from tower
    if (!can_act(t))
        return;

        do_action(t,active,tower);
        next_action_time = t + reload_period +1;
}

void Enemy::move(int t){
    if (state != ACTIVE || is_frozen(t))
        return;

    if (distance <= config::MIN_DISTANCE)
        return;

    if (is_half_health()) {
        move_toggle = !move_toggle;
        if (!move_toggle)
            return;
    }

    distance--;
}

void Enemy::take_damage(double damage_amount , int t){
    if (!is_alive())
        return;

    make_first_shot(t);

    curr_health -= damage_amount;

    if (curr_health <= 0) {
        curr_health = 0;
        state = KILLED;
        kill_time = t;
    }
}

void Enemy::heal(double healing_amount){
    if (!is_alive())
        return;

    curr_health = std::min(original_health, curr_health + healing_amount);
}

void Enemy::freeze(int t , int frozen_time){
    if (!is_alive())
        return;

    // first shot may be ice not bullets
    make_first_shot(t);

    frozen_time = std::min(frozen_time, config::MAX_FREEZE);
    frozen_until = std::max(frozen_until, t + frozen_time);
}

bool Enemy::is_frozen(int t) const{
    return t < frozen_until;
}

bool Enemy::is_half_health(int t){
    return curr_health <= original_health / 2.0;
}

bool Enemy::is_alive(){
    return state != KILLED && curr_health > 0;
}

bool Enemy::can_act(int t){
    return state == ACTIVE && !is_frozen(t) && t >= next_action_time;
}

int Enemy::get_remaining_reload_time(int t){
    return std::max(0, next_action_time - t);
}

double Enemy::get_priority(int t){
    return Formulas::target_priority(distance,power,get_remaining_reload_time(t),
                                    is_frozen(t),
                                    get_type());
}

int Enemy::get_fd(){
    if (first_shot_time == -1)
        return -1;
    return first_shot_time - arrival_time;
}

int Enemy::get_kd(){
    if (kill_time == -1 || first_shot_time == -1)
        return -1;
    return kill_time - first_shot_time;
}

int Enemy::get_lt(){
    if (kill_time == -1)
        return -1;
    return kill_time - arrival_time;
}

void Enemy::set_region(REGION r){
    region = r;
}

void Enemy::set_state(ENEMY_STATE s){
    state = s;
}
