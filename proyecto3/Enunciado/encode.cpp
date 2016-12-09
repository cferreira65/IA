#include <iostream>
#include <stdlib.h>
using namespace std;

int n;
int m;

int q(int i, int j, char d){

    switch(d){
        case 'n' : return (i + (j - 1) * n );
        case 's' : return (i + j * n);
        case 'e' : return ((i - 1) * (m + 1) + j + n * (m + 1) + 1);
        case 'w' : return ((i - 1) * (m + 1) + j + n * (m + 1));
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
    for (int j = 1 ; j <= n; ++j){
        for (int i = 1 ; i <= m; ++i){
            cout << q(i,j,'w') << '\n';
        }
    }
    cout << "--------------\n";
    for (int j = 1 ; j <= n; ++j){
        for (int i = 1 ; i <= m; ++i){
            cout << z(i,j) << '\n';
        }
    }

    return 0;
}