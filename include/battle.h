
#ifndef BATTLE_H
#define BATTLE_H

#include "castle.h"
#include "enemy/enemy.h"
#include "queue/queue.h"
#include "linkedlist/double_linkedlist.h"

class Battle{
private:
Castle castle;
Queue<Enemy*>inactive;
double_linkedlist<Enemy*>active[4];
Queue<Enemy*>killed;
int killed_count[4];
int total_enemies;
int active_count[4][3];
int curr_time;


public:
Battle();
~Battle();
void run(const char *input_file , const char * output_file);
bool load_input(const char * input_file);
void write_output(const char * output_file , GAME_STATE res);
void activate_arrivals(int t);
void enemies_act(int t);
void towers_act(int t);
void remove_killed(int t);
static bool kill_order_before(Enemy *const &a,Enemy *const &b);
void transpost_destroyed();
GAME_STATE check_game_end(int t);

};

#endif