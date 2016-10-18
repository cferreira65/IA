#include <iostream>
#include <fstream>
#include <string>
#include "dfid.h"

using namespace std;

unsigned long int nodes_gen;
int b;

int Dfid::dfid (state_t state, int hist, int d, int bound) {

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

/*int main(int argc, char **argv ) {

    ifstream in;
    in.open (argv[2]);
    ofstream out;
    out.open (argv[3]);
    string line;
    char str[512];

    ssize_t nchars; 
    state_t state;
    int cost;
    int bound;

    b = 1 + atoi(argv[1]);

    out << "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n";

    if (in.is_open()) {
        while (getline (in,line)) {
            sprintf(str, "%.200s", line.c_str());
            read_state(str, &state);
            bound = 0;
            nodes_gen = 0;
            while (true) {
                cost = dfid (state, init_history, 0, bound);
                if (cost!=-1 || bound >= b)
                    break;
                ++bound;

            }
            out << "cost " << cost << ", ";
            out << "generated " << nodes_gen << "\n";

        }
    }
    in.close();
    out.close();
    return 0;
}*/
    