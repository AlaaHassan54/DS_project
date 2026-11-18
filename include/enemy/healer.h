#ifndef HEALER_H
#define HEALER_H

#include "enemy.h"

class Healer : public Enemy
{
public:
ENEMY_TYPE get_type();
void do_action(int t , double_linkedlist<Enemy*>&active , Tower&tower);
};







#endif