#include "battle.h"
#include "config.h"
#include "input_reader.h"
//implement all these functionality (by Ahmed)


// counters for the entire simulation (i will not use them now because of there are no mention to them in the original project requirements, but there mentioned in the last provided pdf)
   // int stall_steps = 0; // incase if game reached a limit, the game will be draw
   // float last_total_damage = 0.0;
   // int last_killed_count = 0;

// ctors
Battle::Battle(){
    total_enemies = 0;
    curr_time = 0;
    //stall_steps = 0;
    //last_total_damage = 0.0;
    //last_killed_count = 0;

    for (int i = 0; i < 4; i++)
    {
        killed_count[i] = 0; // reset killed counter

        for (int j = 0; j < 3; j++)
        {
            active_count[i][j] = 0; // resst active counter
        }
    }


}


Battle::~Battle(){
    // 1 Delete enemies in inactive.
        while (!inactive.isEmpty())
        {
            Enemy* enemy = nullptr;
            if (inactive.dequeu(enemy))
            {
                delete enemy;
            }
        }

    // 2 Delete enemies in each of the four active lists.
    for (int i = 0; i < 4; i++)
    {
        l_node<Enemy*>* current = active[i].get_head(); // TODO: ask alla about get_head

        while (current != nullptr)
        {
            Enemy* enemy = current->d;
            l_node<Enemy*>* next = current->next;

            delete enemy;
            current = next;
        }

        active[i].delete_all_nodes();
    }

    // 3 Delete enemies in killed.
    while (!killed.isEmpty())
    {
        Enemy* enemy = nullptr;

        if (killed.dequeu(enemy))
        {
            delete enemy;
        }
    }
}


void Battle::run(const char *input_file, const char *output_file)
{
    if (!load_input(input_file))
    {
        return;
    }

    curr_time = 1;
    GAME_STATE state = RUNNING;

    while (state == RUNNING)
    {
        activate_arrivals(curr_time);
        enemies_act(curr_time);
        towers_act(curr_time);
        remove_killed(curr_time);
        transpost_destroyed();

        state = check_game_end(curr_time);

        if (state == RUNNING)
        {
            curr_time++;
        }
    }

    write_output(output_file, state);
}


bool Battle::load_input(const char * input_file){
    InputReader input_reader;

    return input_reader.load(input_file, castle, inactive, total_enemies);

}


void Battle::write_output(const char * output_file , GAME_STATE res){ 


}


void Battle::activate_arrivals(int t)
{
    Enemy* enemy = nullptr;

    while (inactive.get_front(enemy))
    {
        if (enemy->get_arrival_time() > t)
            break;

        inactive.dequeu(enemy);

        REGION region = castle.resolve_region(enemy->get_region()); // to check if the tower is still alive other wise go to the next region

        

        enemy->set_region(region);
        enemy->set_state(ACTIVE);

        active[region].append(enemy);
        active_count[region][enemy->get_type()]++;
    }
}


void Battle::enemies_act(int t){
    for (int i = 0; i < 4; i++)
    {
        //  get the tower of this region.
        Tower& tower = castle.get_tower(static_cast<REGION>(i)); // convert from 

        // get first enemy.
        l_node<Enemy*>* current = active[i].get_head(); // TODO: ask alla about get_head

        while (current != nullptr)
        {
            Enemy* enemy = current->d;

            enemy->act(t, active[i], tower);
            enemy->move(t);

            current = current->next;
        }
    }

}


void Battle::towers_act(int t)
{
    for (int i = 0; i < 4; i++)
    {
        Tower& tower = castle.get_tower(static_cast<REGION>(i));

        tower.act(t, active[i]);
    }
}



void Battle::remove_killed(int t)
{
    double_linkedlist<Enemy*> sorted; // create a temp doubl linked list  to hold Enemy* pointers while organizing them.

    Enemy* enemy = nullptr;

    // 1 move previously killed enemies into sorted list
    while (killed.dequeu(enemy))
    {
        sorted.insert_sorted(enemy, kill_order_before);
    }

    // 2  find newly killed enemies.
    for (int i = 0; i < 4; i++)
    {
        l_node<Enemy*>* current = active[i].get_head();

        while (current != nullptr)
        {
            Enemy* enemy = current->d;

            if (!enemy->is_alive())
            {
                int type = enemy->get_type();

                current = active[i].remove(current);

                active_count[i][type]--;

                enemy->set_state(KILLED);

                killed_count[i]++;

                sorted.insert_sorted(enemy, kill_order_before);
            }
            else
            {
                current = current->next;
            }
        }
    }

    // 3 restore the sorted enemies into killed queue.
    while (sorted.pop_front(enemy))
    {
        killed.enqueu(enemy);
    }
}


bool Battle::kill_order_before(Enemy *const &a, Enemy *const &b)
{
    if (a == nullptr || b == nullptr)
    {
        return false;
    }

    if (a->get_fd() != b->get_fd()) // if two enemies not have the same first shot delay
    {
        return a->get_fd() < b->get_fd();
    }

        return a->get_id() < b->get_id(); // if they have the same shot time delay check for id order 
}



void Battle::transpost_destroyed()
{
    for (int r = 0; r < 4; r++)
    {
        REGION reg = static_cast<REGION>(r);
        Tower& tower = castle.get_tower(reg);

        if (tower.is_destroyed(curr_time)) // transports enemies when that region's tower is destroyed.
        {
            REGION target = castle.resolve_region(reg);

            // if (target == NONE) // TODO: we need to check for NONE,
            // {
            //     return;
            // }

            l_node<Enemy*>* current = active[r].get_head();

            while (current != nullptr)
            {
                l_node<Enemy*>* next = current->next;
                Enemy* enemy = current->d;

                if (enemy != nullptr)
                {
                    int type = enemy->get_type();

                    active_count[r][type]--;

                    enemy->set_region(target);
                    active[target].append(enemy);
                    active_count[target][type]++;

                    active[r].delete_node_by_value(enemy);
                }

                current = next;
            }
        }
    }
}



GAME_STATE Battle::check_game_end(int t)
{
    int destroyed_towers = 0;
    for (int r = 0; r < 4; r++)
    {
        if (castle.get_tower(static_cast<REGION>(r)).is_destroyed(t))
        {
            destroyed_towers++;
        }
    }

    if (destroyed_towers == 4)
    {
        return LOSS;
    }

    int remaining_active = 0;
    for (int r = 0; r < 4; r++)
    {
        for (int type = 0; type < 3; type++)
        {
            remaining_active += active_count[r][type];
        }
    }

    if (inactive.isEmpty() && remaining_active == 0)
    {
        return WIN;
    }

    return RUNNING;
}