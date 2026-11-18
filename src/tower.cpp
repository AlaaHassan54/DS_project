#include "tower.h"
#include "config.h"
#include "formulas.h"



//implement all these functionality (by Hanaa)


Tower::Tower(){



}



Tower::~Tower(){


}


void Tower::init(REGION _region , double _start_health , double _power , int _num_targets){




}


void Tower::act(int t , double_linkedlist<Enemy*>& active){



}


int Tower::pick_targets(int t ,double_linkedlist<Enemy*>& active){



}


bool Tower::can_fire_ice(int t , const Enemy * enemy){



}


void Tower::fire_bullets(int t ,Enemy * enemy){


}


void Tower::fire_ice(int t ,Enemy * enemy){



}


void Tower::take_damage(double damage_amount){


}


void Tower::take_ice(double ice_amount , int t){



}



bool Tower::is_frozen(int t){



}


bool Tower::is_destroyed(int t){


}



REGION Tower::get_region(){



}


double Tower::get_curr_health(){




}


double Tower::get_start_health(){


}



double Tower::get_power(){



}


int Tower::get_num_targets(){



}



double Tower::get_total_damage_taken(){



}