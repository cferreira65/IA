
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "dfid.h"


using namespace std;

unsigned long int nodes_gen;

int main(int argc, char **argv ) {

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

    std::clock_t start;
    double duration;

    b = 1 + atoi(argv[1]);

    out << "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n";

    if (in.is_open()) {
        while (getline (in,line)) {
            sprintf(str, "%.200s", line.c_str());
            read_state(str, &state);
            bound = 0;
            nodes_gen = 0;
            while (true) {
                start = std::clock();
                cost = Dfid::dfid (state, init_history, 0, bound);
                duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
                if (cost!=-1 || bound >= b)
                    break;
                ++bound;

            }
            out << "cost " << cost << ", ";
            out << "generated " << nodes_gen << "\n";
            out << "time " << duration << "\n";

        }
    }
    in.close();
    out.close();
    return 0;
}
    