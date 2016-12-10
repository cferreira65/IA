#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

int n;
int m;
int seg;

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
    return (i + (j - 1) * n + seg);
}

int r(int i, int j, int x, int y){
    int ncel = n*m;
    int cel1 = i + (j - 1) * n;
    int cel2 = x + (y - 1) * n;
    return ((cel1 - 1) * ncel + cel2 + seg + ncel);
}

int main(int argc, char const *argv[])
{
    ifstream in (argv[1]);
    ofstream myfile ("encode.cnf");
    in >> n;
    in >> m;
    seg = (m + 1) * n + m * (n + 1);
    int var = n * m + seg;
    int cla = 0; 
    myfile << "p cnf " << var << ' ' << cla << '\n';
    char cel;

    for (int j = 1 ; j <= m; ++j){
        for (int i = 1 ; i <= n; ++i){
            myfile << "c Tipo 0\n";
            myfile << -q(i,j,'e') << ' ' << q(i+1,j,'w') << " 0\n";
            myfile << q(i,j,'e') << ' ' << -q(i+1,j,'w') << " 0\n";
            myfile << -q(i,j,'s') << ' ' << q(i,j+1,'n') << " 0\n";
            myfile << q(i,j,'s') << ' ' << -q(i,j+1,'n') << " 0\n";
            
            myfile << "c Tipo 1\n";
            in >> cel;

            switch(cel){
                case '0' :
                    myfile << -q(i,j,'n') << " 0\n";
                    myfile << -q(i,j,'s') << " 0\n";
                    myfile << -q(i,j,'e') << " 0\n";
                    myfile << -q(i,j,'w') << " 0\n";
                    break;
                case '1' :
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << ' ' << q(i,j,'s') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'e') << " 0\n";
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'s') << " 0\n"; 
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'w') << " 0\n"; 
                    myfile << -q(i,j,'e') << ' ' << -q(i,j,'s') << " 0\n"; 
                    myfile << -q(i,j,'e') << ' ' << -q(i,j,'w') << " 0\n"; 
                    myfile << -q(i,j,'s') << ' ' << -q(i,j,'w') << " 0\n"; 
                    break;
                case '2' :
                    //[q(i,j,n) v q(i,j,e) v q(i,j,s)] /\ [q(i,j,n) v q(i,j,e) v q(i,j,w)] /\ [q(i,j,n) v q(i,j,e) v q(i,j,w) v q(i,j,s)] /\ [q(i,j,n) v q(i,j,s) v q(i,j,w)] /\ [q(i,j,e) v q(i,j,s) v q(i,j,w)]
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << ' ' << q(i,j,'s') << " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << ' ' << q(i,j,'w') << " 0\n";
                    //Creo que el w no va
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << ' ' << q(i,j,'w') << ' ' << q(i,j,'s')<< " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'s') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << q(i,j,'e') << ' ' << q(i,j,'s') << ' ' << q(i,j,'w') << " 0\n";

                    // -q(i,j,n) v -q(i,j,e) v -q(i,j,s)
                    // -q(i,j,n) v -q(i,j,e) v -q(i,j,w)
                    // -q(i,j,e) v -q(i,j,s) v -q(i,j,w)
                    // -q(i,j,e) v -q(i,j,s) v -q(i,j,n)
                    // -q(i,j,s) v -q(i,j,w) v -q(i,j,n)
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'s') << " 0\n";
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'w') << " 0\n";
                    myfile << -q(i,j,'e') << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'w') << " 0\n";
                    myfile << -q(i,j,'e') << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'n') << " 0\n";
                    myfile << -q(i,j,'s') << ' ' << -q(i,j,'w') << ' ' << -q(i,j,'n') << " 0\n";
                    break;
                case '3' :
                    //[q(i,j,n) v q(i,j,e) v q(i,j,s) v q(i,j,w)] /\ 
                    //[q(i,j,n) v q(i,j,e) v q(i,j,s)] /\ 
                    //[q(i,j,n) v q(i,j,e) v q(i,j,w)] /\ 
                    //[q(i,j,n) v q(i,j,e)] /\ 
                    //[q(i,j,n) v q(i,j,s) v q(i,j,w)] /\ 
                    //[q(i,j,n) v q(i,j,s)] /\ 
                    //[q(i,j,n) v q(i,j,w)] /\ 
                    //[q(i,j,e) v q(i,j,s) v q(i,j,w)] /\ 
                    //[q(i,j,e) v q(i,j,s)] /\ 
                    //[q(i,j,e) v q(i,j,w)] /\ 
                    //[q(i,j,s) v q(i,j,w)]
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << ' ' << q(i,j,'s') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << ' ' << q(i,j,'s') << " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'e') << " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'s') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'s') << " 0\n";
                    myfile << q(i,j,'n') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << q(i,j,'e') << ' ' << q(i,j,'s') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << q(i,j,'e') << ' ' << q(i,j,'s') << " 0\n";
                    myfile << q(i,j,'e') << ' ' << q(i,j,'w') << " 0\n";
                    myfile << q(i,j,'s') << ' ' << q(i,j,'w') << " 0\n";
                    //-q(i,j,n) v -q(i,j,e) v -q(i,j,s) v -q(i,j,w)
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'w') << " 0\n";
                    break;
                case '4' :
                    // q(i,j,n)
                    // q(i,j,e)
                    // q(i,j,s)
                    // q(i,j,w)
                    myfile << q(i,j,'n') << " 0\n";
                    myfile << q(i,j,'e') << " 0\n";
                    myfile << q(i,j,'s') << " 0\n";
                    myfile << q(i,j,'w') << " 0\n";
                    break;

            }
        }
    }
    in.close();
    myfile.close();
    

    return 0;
}