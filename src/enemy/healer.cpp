
#include "formulas.h"
#include "config.h"
#include "enemy/healer.h"


//implement all these functionality (by Basmala)



ENEMY_TYPE Healer::get_type(){

return HEALER;


}



void Healer::do_action(int t , double_linkedlist<Enemy*>&active , Tower&tower){

    auto* current=active_list.get_head();
    while(current !=nullptr)
    {
        enemy*e=current->item;
        if(e != this && e->is_alive())
        {
            int distance_diff=abs(e->get_distance()-get_distance());
            if(distance_diff<=heal_range)
            {
                e->heal(
                    heal_amount(
                        get_power(),
                        distance_diff
                    )
                );
            }
        }
        current=current->next;

        }
    }
    
    

