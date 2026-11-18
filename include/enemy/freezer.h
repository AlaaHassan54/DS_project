#ifndef FREEZER_H
#define FREEZER_H

#include "enemy.h"

class Freezer : public Enemy
{
public:
ENEMY_TYPE get_type();
void do_action(int t , double_linkedlist<Enemy*>&active , Tower&tower);
};







#endif