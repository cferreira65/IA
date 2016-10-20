#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

unsigned long int nodes_gen;
int b;

int dfid (state_t state, int hist, int d, int bound) {

    if (d > bound) 
        return -1;

    if (is_goal(&state))
        return d;

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    int aux;
    int res;

    // LOOP THOUGH THE CHILDREN ONE BY ONE
    init_fwd_iter(&iter, &state);  // initialize the child iterator
    while( (ruleid = next_ruleid(&iter)) >= 0 ) {
        if (fwd_rule_valid_for_history(hist,ruleid)) {
            aux = next_fwd_history(hist,ruleid);
            apply_fwd_rule(ruleid, &state, &child);
            ++nodes_gen; 
            res = dfid(child, aux, d+1, bound);
            if (res != -1)
                return res;
        }
    }
    return -1;
}

int main(int argc, char **argv ) {

    int cost;
    int bound;
    char str[512];
    state_t state;
    clock_t t_init, t_end;
    double time_elap;
    double gen_per_sec;

    read_state(argv[1], &state);
    bound = 0;
    nodes_gen = 0;
    t_init = clock();

    while (true) {
        cost = dfid (state, init_history, 0, bound);
        if (cost!=-1)
            break;
        ++bound;
        }

    t_end = clock();
    time_elap = double(t_end - t_init)/CLOCKS_PER_SEC;
    gen_per_sec = double(nodes_gen)/time_elap;

    cout << "X, dfid, " << argv[2] << ", \"" << argv[1] << "\", ";
    cout << cost << ", ";
    cout << nodes_gen << ", ";
    cout << time_elap << ", ";
    cout << gen_per_sec << "\n";
    return 0;
}

    