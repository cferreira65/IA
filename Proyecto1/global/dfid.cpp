#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv ) {

    ifstream in;
    in.open (argv[1]);
    ofstream out;
    out.open (argv[2]);
    string line;

    out << "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec\n"

    if (in.is_open()) {
        while (getline (in,line)) {
            out << line << "\n";
        }
    }
    in.close();
    out.close();
    return 0;
}
    