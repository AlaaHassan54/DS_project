#include "formulas.h"
#include "config.h"
#include "enemy/fighter.h"

//implement all these functionality (by Basmala)

ENEMY_TYPE Fighter::get_type(){

return FIGHTER;

}



void Fighter::do_action(int t , double_linkedlist<Enemy*>&active , Tower&tower){

double damage=formulas::fighter_damage(get_power(),get_distance(),is_half_health(t));
tower.take_damage(damage);
}
