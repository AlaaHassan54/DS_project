#ifndef ENUMS_H
#define ENUMS_H


enum REGION{
A = 0,
B = 1,
C = 2,
D = 3,
};

enum ENEMY_STATE{
 INACTIVE = 0,
 ACTIVE = 1,
 KILLED = 2,  

};


enum ENEMY_TYPE{
FIGHTER = 0,
HEALER = 1,
FREEZER = 2,
};

enum GAME_STATE{
RUNNING = 0,
WIN = 1,
LOSS = 2,
DRAWN = 3,
};



#endif