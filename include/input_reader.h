#ifndef INPUT_READER_H
#define INPUT_READER_H

#include "castle.h"
#include "enemy/enemy.h"
#include "queue/queue.h"
#include "enums.h"

class InputReader
{
public:
    bool load(const char* input_file, Castle& castle, Queue<Enemy*>& inactive, int& total_enemies);
};

#endif