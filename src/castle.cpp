#include "castle.h"

//implement all these functionality (by Basmala)

Castle::Castle(){


}



Castle::~Castle(){


}



void Castle::init(double start_health , double power,int num_targets){

for(int i=0; i<4; i++)
{
    towers[i].init(static_cast<REGION>(i),start_health,power,num_targets);


}


}


Tower & Castle::get_tower(REGION r){

return towers[r];


}



REGION Castle::resolve_region(REGION r){

for(int i=0; i<4; i++)
{
    int candidate=(static_cast<int>(r)+i) %4;
    if(!towers[candidate].is_destroyed(0))
    {
        return static_cast<REGION>(candidate);
    }
}
return NONE;

}



bool Castle::is_all_destroyed(){
for(int i=0; i<4; i++)
{
    if(!towers[i].is_destroyed(0))
    {
        return false;
    }
}
return true;

}


double Castle::get_total_damage(REGION r){

    return towers[r].get_total_damage_taken();


}


double Castle::get_health(REGION r){

return towers[r].get_curr_health();



}