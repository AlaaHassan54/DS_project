
#include "formulas.h"
#include "config.h"
#include "enemy/freezer.h"


//implement all these functionality (by Basmala)



ENEMY_TYPE Freezer::get_type(){

    return FREEZER;


}



void Freezer::do_action(int t , double_linkedlist<Enemy*>&active , Tower&tower){

    double ice=ice_per_shot(get_power(),get_distance());
tower.take_ice(ice,t);
}