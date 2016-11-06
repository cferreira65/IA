#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "priority_queue.hpp"

using namespace std;

struct node {
    state_t state;
    int d;
};

unsigned long int nodes_gen;


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

int aStar (state_t state){

    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    state_map_t *map = new_state_map();
    state_map_t *hist_map = new_state_map();
    PriorityQueue<node> q;
    node n;
    node child_n;
    n.state = state;
    n.d = 0;
    int h0 = gap(state);
    state_map_add(map, &state, h0);
    state_map_add(hist_map, &state, init_history);
    q.Add(0, 0, n);
    //int f = d + manhattan(state);
    //node expand;
    state_t child;
    int aux;


    while(!q.Empty()){

        n = q.Top();
        int cp = q.CurrentPriority();
        q.Pop();
        int *g = state_map_get(map,&n.state);
        int *hist = state_map_get(hist_map,&n.state);
        print_state(stdout, &n.state);

        state_map_add(map, &n.state, n.d);
        if (is_goal(&n.state))
            return n.d;

        init_fwd_iter(&iter, &n.state);  // initialize the child iterator
        while ( (ruleid = next_ruleid(&iter)) >= 0 ){
            if (fwd_rule_valid_for_history(*hist,ruleid)){
                    
                aux = next_fwd_history(*hist,ruleid);
                apply_fwd_rule(ruleid, &n.state, &child);
                ++nodes_gen;
                child_n.state = child;
                child_n.d = n.d + 1;
                state_map_add(map,&child_n.state,child_n.d);
                state_map_add(hist_map,&child_n.state,aux);
                int c = child_n.d + gap(child_n.state);
                q.Add(c, c, child_n);
            }
        }
    }

    return -1;
}

int main(int argc, char **argv ) {

    int cost;
    char str[512];
    state_t state;
    clock_t t_init, t_end;
    double time_elap;
    double gen_per_sec;

    nodes_gen = 0;
    read_state(argv[1], &state);
    ++nodes_gen;
    t_init = clock();

    cost = aStar(state);

    t_end = clock();
    time_elap = double(t_end - t_init)/CLOCKS_PER_SEC;
    gen_per_sec = double(nodes_gen)/time_elap;

    cout << "X, a*, gap, " << argv[2] << ", \"" << argv[1] << "\", ";
    cout << cost << ", ";
    cout << gap(state) << ", ";
    cout << nodes_gen << ", ";
    cout << time_elap << ", ";
    cout << gen_per_sec << "\n";
    return 0;

}