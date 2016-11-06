#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <sstream>

using namespace std;

unsigned long long int nodes_gen;
unsigned long long int lqs;

int gap (state_t state){

    int i = 0;
    int h = 0;

    while (i < 27){

        if ( abs(state.vars[i] - state.vars[i+1]) != 1 )
            h++;
        i++;

    }
    if (state.vars[i] != 27)
        h++;

    return h;
}

std::pair<int,int> ida (state_t state, int hist, int d, int bound){

    std::pair<int,int> node;

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    int aux;
    std::pair<int,int> res;
    int t;

    int f = d + gap(state);
    if (f > bound){
        node.first = -1;
        node.second = f;
        return node;
    }

    if (is_goal(&state)) {
        node.first = 0;
        node.second = d;
        return node;
    }

    t = 10000000;

    // LOOP THOUGH THE CHILDREN ONE BY ONE
    init_fwd_iter(&iter, &state);  // initialize the child iterator
    while ( (ruleid = next_ruleid(&iter)) >= 0 ){
        if (fwd_rule_valid_for_history(hist,ruleid)){
            
            aux = next_fwd_history(hist,ruleid);
            apply_fwd_rule(ruleid, &state, &child);
            ++nodes_gen; 
            res = ida(child, aux, d+1, bound);
            if (res.first != -1) {
                return res;}
            t = min(t,res.second);

        }

    }

    node.first = -1;
    node.second = t;
    return node;

}

int main(int argc, char **argv ) {

    std::pair<int,int> cost;
    int bound;
    char str[512];
    state_t state;
    clock_t t_init, t_end;
    double time_elap;
    double gen_per_sec;
    int h,

    lqs = 0;
    nodes_gen = 0;
    read_state(argv[1], &state);
    ++nodes_gen;
    bound = gap(state);
    h = bound;
    t_init = clock();

    ++nodes_gen;

    while (true) {
        cost = ida (state, init_history, 0, bound);
        if (cost.first!=-1)
            break;
        bound = cost.second;
        }

    t_end = clock();
    time_elap = double(t_end - t_init)/CLOCKS_PER_SEC;
    gen_per_sec = double(nodes_gen)/time_elap;

    cout << "X, ida, gap, " << argv[2] << ", \"" << argv[1] << "\", ";
    cout << cost.second << ", ";
    cout << h << ", ";
    cout << nodes_gen << ", ";
    cout << time_elap << ", ";
    cout << gen_per_sec << "\n";
    return 0;
}
