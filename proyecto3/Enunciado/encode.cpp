#include <iostream>
#include <stdlib.h>
using namespace std;

int n;
int m;

int q(int i, int j, char d){

    switch(d){
        case 'n' : return (i + (j - 1) * n );
        case 's' : return (i + j * n);
        case 'e' : return (i + (j - 1) * (m + 1) + n * (m + 1) + 1);
        case 'w' : return (i + (j - 1) * (m + 1) + n * (m + 1));
    }
    return 0;
}

int z(int i, int j){
    int val = (m + 1) * n + m * (n + 1);
    return (i + (j - 1) * n + val);
}

int main(int argc, char const *argv[])
{
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    int var = n * m + (n+1) * m + n * (m+1);
    int cla = 0; 
    cout << "p cnf " << var << ' ' << cla << '\n';

    for (int j = 1 ; j <= m; ++j){
        for (int i = 1 ; i <= n; ++i){
            cout << -q(i,j,'e') << ' ' << q(i+1,j,'w') << " 0\n";
            cout << q(i,j,'e') << ' ' << -q(i+1,j,'w') << " 0\n";
            cout << -q(i,j,'s') << ' ' << q(i,j+1,'n') << " 0\n";
            cout << q(i,j,'s') << ' ' << -q(i,j+1,'n') << " 0\n";
            
        }
    }
    

    return 0;
}