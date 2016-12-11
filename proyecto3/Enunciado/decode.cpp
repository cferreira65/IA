#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in (argv[1]);
    ofstream out ("out.cnf");
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    out << n << ' ';
    out << m << ' ';
    string hor[n+1];
    string ver[m];
    string temp;
    in >> temp;
    int seg;

    for (int j = 0 ; j < m+1 ; ++j){
        temp = "";
        for (int i = 0 ; i < n ; ++i){
            in >> seg;
            if (seg < 0)
                temp = temp + "0";
            else
                temp = temp + "1";
        }
        temp = temp + " ";
        hor[j] = temp;
    }

    for (int i = 0 ; i < n ; ++i){
        temp = "";
        for (int j = 0 ; j < m+1 ; ++j){
            in >> seg;
            if (seg < 0)
                temp = temp + "0";
            else
                temp = temp + "1";
        }
        temp = temp + " ";
        ver[i] = temp;
    }

    for (int i = 0; i < n; ++i){
        out << hor[i];
        out << ver[i];
    }
    out << hor[n];
    
    return 0;
}