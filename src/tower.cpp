#include "tower.h"
#include "config.h"
#include "formulas.h"
#include "enemy.h"
#include <cstdlib>

//implement all these functionality (by Hanaa)
Tower::Tower() : targets(0), accumulated_ice(0), frozen_until(0),
    total_shots(0), ice_shots(0), total_damage_taken(0), num_targets(0) {}

Tower::~Tower(){
    delete[] targets;
}


void Tower::init(REGION _region , double _start_health , double _power , int _num_targets)
{
    region = _region;
    power = _power;
    start_health = _start_health;
    curr_health = _start_health;
    num_targets = _num_targets;

    delete[] targets;                      
    targets = new Enemy*[num_targets];

    accumulated_ice = 0;
    total_damage_taken = 0;
    total_shots = 0;
    ice_shots = 0;
    frozen_until = 0;


}


void Tower::act(int t , double_linkedlist<Enemy*>& active)
{
    if (is_destroyed(t) || is_frozen(t)) return;

    int count = pick_targets(t, active);
    for (int i = 0; i < count; i++) 
    {
        if (!targets[i]->is_alive()) continue;

        if (can_fire_ice(t, targets[i]))
            fire_ice(t, targets[i]);
        else
            fire_bullets(t, targets[i]);

        total_shots = total_shots + 1;
    }
}


int Tower::pick_targets(int t ,double_linkedlist<Enemy*>& active)
{
    int count = 0;
    for (auto* node = active.get_head(); node != 0; node = node->next) {
        Enemy* e = node->item;
        if (!e->is_alive()) continue;

        double p = e->get_priority(t);
        int slot;

        if (count < num_targets) {
            slot = count;                      
        } else if (num_targets > 0 && p > targets[count - 1]->get_priority(t)) {
            slot = count - 1;                          
        } else {
            continue;                                  
        }

        // shift weaker enemies down
        while (slot > 0 && targets[slot - 1]->get_priority(t) < p) {
            targets[slot] = targets[slot - 1];
            slot = slot - 1;
        }
        targets[slot] = e;

        if (count < num_targets) count = count + 1;
    }
    return count;
}


bool Tower::can_fire_ice(int t , const Enemy * enemy)
{
    if (5 * (ice_shots + 1) > total_shots + 1) return false;
    if (enemy->is_frozen(t)) return false;
    return (rand() % 100) < config::ICE_CHANCE_PERCENT;
}


void Tower::fire_bullets(int t ,Enemy * enemy)
{
    double damage = Formulas::bullet_damage(power, enemy->get_distance(), enemy->get_type());
    enemy->take_damage(damage, t);
}


void Tower::fire_ice(int t ,Enemy * enemy)
{
    int steps = Formulas::freeze_duration(power, enemy->get_distance());
    enemy->freeze(t, steps);
    ice_shots = ice_shots + 1; 
}


void Tower::take_damage(double damage_amount)
{
    if (curr_health <= 0) return;         

    if (damage_amount > curr_health)     
        damage_amount = curr_health;

    curr_health = curr_health - damage_amount;
    total_damage_taken = total_damage_taken + damage_amount;
}


void Tower::take_ice(double ice_amount , int t)
{
    if (curr_health <= 0 || is_frozen(t)) return;

    accumulated_ice = accumulated_ice + ice_amount;
    if (accumulated_ice >= config::ICE_THRESHOLD) {
        frozen_until = t + 1;
        accumulated_ice = 0;
    }

}



bool Tower::is_frozen(int t)
{
     return t < frozen_until;
}


bool Tower::is_destroyed(int t)
{
    return curr_health <= 0;
}



REGION Tower::get_region()
{
    return region;
}


double Tower::get_curr_health()
{
    return curr_health;
}


double Tower::get_start_health()
{
     return start_health;
}



double Tower::get_power()
{
    return power;
}


int Tower::get_num_targets()
{
    return num_targets;
}



double Tower::get_total_damage_taken()
{
    return total_damage_taken;
}