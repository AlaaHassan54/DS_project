#include <iostream>
#include "config.h"
#include <fstream> 
#include "linkedlist/double_linkedlist.h"
#include "queue/queue.h"
#include "tower.h"
#include "castle.h"
using namespace std;


bool redirectIO(const char* inPath, const char* outPath)
{
    if (!std::freopen(inPath, "r", stdin)) {
        std::fprintf(stderr, "Cannot open %s\n", inPath);   
        return false;
    }
    if (!std::freopen(outPath, "w", stdout)) {
        std::fprintf(stderr, "Cannot open %s\n", outPath);
        return false;
    }
    return true;
}


int main()
{

if (!redirectIO("data/input/input.txt", "data/output/output.txt")) return 1;

    Tower t;
    Castle c;
    return 0;
}