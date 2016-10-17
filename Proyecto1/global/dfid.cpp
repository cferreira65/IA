#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void DFS (state_t state, int hist, int d) {

    if (d > b) 
        return;

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    int aux;

    // LOOP THOUGH THE CHILDREN ONE BY ONE
    init_fwd_iter(&iter, &state);  // initialize the child iterator
    ++ns[d]; 
    while( (ruleid = next_ruleid(&iter)) >= 0 ) {
        if (fwd_rule_valid_for_history(hist,ruleid)) {
            aux = next_fwd_history(hist,ruleid);
            apply_fwd_rule(ruleid, &state, &child);
            DFS (child, aux, d+1);
        }

    }

int main(int argc, char **argv ) {

    ifstream in;
    in.open (argv[1]);
    ofstream out;
    out.open (argv[2]);
    string line;

    ssize_t nchars; 
    state_t state;

    out << "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n"

    if (in.is_open()) {
        while (getline (in,line)) {
            nchars = read_state(line, &state);
            if( nchars <= 0 ) {
                printf("Error: invalid state entered.\n");
                return 0;
    }
            out << line << "\n";
        }
    }
    in.close();
    out.close();
    return 0;
}
    