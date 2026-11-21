#include "input_reader.h"
#include <fstream>

#include "enemy/fighter.h"
#include "enemy/healer.h"
#include "enemy/freezer.h"

bool InputReader::load(const char* input_file, Castle& castle, Queue<Enemy*>& inactive, int& total_enemies)
{
    std::ifstream file(input_file);

    if (!file.is_open()) // if it failed to open the file then return
        return false;

    double TH, TP;
    int N;

    file >> TH;
    file >> N ;
    file >> TP;

    if (file.fail()) // if it failed reading the input stratm then return
        return false;

    castle.init(TH, TP, N);

    total_enemies = 0;

    int id;

    while (file >> id && id != -1)
    {
        int type;
        int arrival_time;
        double health;
        double power;
        int reload_period;
        char region_char;

        file >> type;
        file >> arrival_time;
        file >> health ;
        file >> power;
        file >> reload_period;
        file >> region_char;

        if (file.fail())
            return false;

        REGION region;

switch (region_char)
    {
        case 'A':
            region = A;
            break;

        case 'B':
            region = B;
            break;

        case 'C':
            region = C;
            break;

        case 'D':
            region = D;
            break;

        default:
            return false;
    }

        Enemy* enemy = nullptr;

        switch (type)
        {
            case 1:
                enemy = new Fighter(id, arrival_time, health, power, reload_period, region);
                break;

            case 2:
                enemy = new Healer(id, arrival_time, health, power, reload_period, region);
                break;

            case 3:
                enemy = new Freezer(id, arrival_time, health, power, reload_period, region);
                break;

            default:
                return false;
        }

        inactive.dequeu(enemy);
        total_enemies++;
    }

    file.close();

    return true;
}