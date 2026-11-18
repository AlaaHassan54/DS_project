#ifndef FIGHTER_H
#define FIGHTER_H

#include "enemy.h"

class Fighter : public Enemy
{
public:
ENEMY_TYPE get_type();
void do_action(int t , double_linkedlist<Enemy*>&active , Tower&tower);
};







#endif