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
        
        myfile << "c Tipo 2\n";
        //[q(1,j,w) v z(1,j)] /\ [-q(1,j,w) v -z(1,j)]
        myfile << q(1,j,'w') << ' ' << z(1,j) << " 0\n";
        myfile << -q(1,j,'w') << ' ' << -z(1,j) << " 0\n";
        //[q(N,j,e) v z(N,j)] /\ [-q(N,j,e) v -z(N,j)]
        myfile << q(n,j,'e') << ' ' << z(n,j) << " 0\n";
        myfile << -q(n,j,'e') << ' ' << -z(n,j) << " 0\n";



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
                    // -q(i,j,s) v -q(i,j,w) v -q(i,j,n)
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'s') << " 0\n";
                    myfile << -q(i,j,'n') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'w') << " 0\n";
                    myfile << -q(i,j,'e') << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'w') << " 0\n";
                    myfile << -q(i,j,'s') << ' ' << -q(i,j,'w') << ' ' << -q(i,j,'n') << " 0\n";
                    break;
                case '3' :
                    //[q(i,j,n) v q(i,j,e) v q(i,j,s) v q(i,j,w)] / 
                    //[q(i,j,n) v q(i,j,e) v q(i,j,s)] /
                    //[q(i,j,n) v q(i,j,e) v q(i,j,w)] / 
                    //[q(i,j,n) v q(i,j,e)] / 
                    //[q(i,j,n) v q(i,j,s) v q(i,j,w)] / 
                    //[q(i,j,n) v q(i,j,s)] /
                    //[q(i,j,n) v q(i,j,w)] / 
                    //[q(i,j,e) v q(i,j,s) v q(i,j,w)] / 
                    //[q(i,j,e) v q(i,j,s)] /
                    //[q(i,j,e) v q(i,j,w)] / 
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
            myfile << "c Tipo 3\n";
            //r(c,c)
            myfile << r(i,j,i,j) << " 0\n";

            for (int y = 1; y <= m; ++y){
                for (int x = 1; x <= n; ++x){
                    if (y-1 != 0){
                        //-r(c,c') v q(c',n) v r(c,c'')
                        myfile << -r(i,j,x,y) << ' ' << q(i,j,'n') << r(i,j,x,y-1) << " 0\n";
                    }

                    if (x != n){
                        //-r(c,c') v q(c',e) v r(c,c'')
                        myfile << -r(i,j,x,y) << ' ' << q(i,j,'e') << r(i,j,x+1,y) << " 0\n";
                    }

                    if (y != m){
                        //-r(c,c') v q(c',s) v r(c,c'')
                        myfile << -r(i,j,x,y) << ' ' << q(i,j,'s') << r(i,j,x,y+1) << " 0\n";
                    }

                    if (x-1 != 0){
                        //-r(c,c') v q(c',w) v r(c,c'')
                        myfile << -r(i,j,x,y) << ' ' << q(i,j,'w') << r(i,j,x-1,y) << " 0\n";
                    }

                    myfile << "c Tipo 4\n";
                    //-z(c) v -z(c') v r(c,c')
                    myfile << -z(i,j) << ' ' << -z(x,y) << r(i,j,x,y) << " 0\n";

                }
            }

        }       
    }

    for (int i = 1 ; i <= n; ++i){
        myfile << "c Tipo 2\n";
        //[q(i,1,n) v z(i,1)] /\ [-q(i,1,n) v -z(i,1)]
        myfile << q(i,1,'n') << ' ' << z(i,1) << " 0\n";
        myfile << -q(i,1,'n') << ' ' << -z(i,1) << " 0\n";
        //[q(i,M,s) v z(i,M)] /\ [-q(i,M,s) v -z(i,M)]
        myfile << q(i,m,'s') << ' ' << z(i,m) << " 0\n";
        myfile << -q(i,m,'s') << ' ' << -z(i,m) << " 0\n";
    }

    for (int j = 2; j < m; ++j){
        for (int i = 2; i < n; ++i){
        
            myfile << "c Tipo 2\n";
            //[-z(i,j) v -q(i,j,s) v -q(i,j,e) v -q(i,j,n) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'n') << ' ' << q(i,j,'w') << " 0\n";
            //[-z(i,j) v -q(i,j,s) v -q(i,j,e) v -q(i,j,n) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'n') << ' ' << z(i-1,j) << " 0\n";
            //[-z(i,j) v -q(i,j,s) v -q(i,j,e) v z(i,j-1) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'w') << ' ' << z(i,j-1) << " 0\n";
            //[-z(i,j) v -q(i,j,s) v -q(i,j,e) v z(i,j-1) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'e') << ' ' << z(i,j-1) << ' ' << z(i-1,j) << " 0\n";
            //[-z(i,j) v -q(i,j,s) v z(i+1,j) v -q(i,j,n) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'n') << ' ' << -q(i,j,'w') << ' ' << z(i+1,j) << " 0\n";
            //[-z(i,j) v -q(i,j,s) v z(i+1,j) v -q(i,j,n) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'n') << ' ' << z(i+1,j) << ' ' << z(i-1,j) << " 0\n";
            //[-z(i,j) v -q(i,j,s) v z(i+1,j) v z(i,j-1) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'w') << ' ' << z(i+1,j) << ' ' << z(i,j-1) << " 0\n";
            //[-z(i,j) v -q(i,j,s) v z(i+1,j) v z(i,j-1) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << z(i+1,j) << ' ' << z(i,j-1) << ' ' << z(i-1,j) << " 0\n";
            //[-z(i,j) v z(i,j+1) v -q(i,j,e) v -q(i,j,n) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'n') << ' ' << -q(i,j,'w') << ' ' << z(i,j+1) << " 0\n";
            //[-z(i,j) v z(i,j+1) v -q(i,j,e) v -q(i,j,n) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'n') << ' ' << z(i,j+1) << ' ' << z(i-1,j) << " 0\n"; 
            //[-z(i,j) v z(i,j+1) v -q(i,j,e) v z(i,j-1) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'w') << ' ' << z(i,j+1) << ' ' << z(i,j-1) << " 0\n";
            //[-z(i,j) v z(i,j+1) v -q(i,j,e) v z(i,j-1) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'e') << ' ' << z(i,j+1) << ' ' << z(i,j-1) << ' ' << z(i-1,j) << " 0\n";
            //[-z(i,j) v z(i,j+1) v z(i+1,j) v -q(i,j,n) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'n') << ' ' << -q(i,j,'w') << ' ' << z(i,j+1) << ' ' << z(i+1,j) << " 0\n";
            //[-z(i,j) v z(i,j+1) v z(i+1,j) v -q(i,j,n) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'n') << ' ' << z(i,j+1) << ' ' << z(i+1,j) << ' ' << z(i-1,j) << " 0\n";
            //[-z(i,j) v z(i,j+1) v z(i+1,j) v z(i,j-1) v -q(i,j,w)] /
            myfile << -z(i,j) << ' ' << -q(i,j,'w') << ' ' << z(i,j+1) << ' ' << z(i+1,j) << ' ' << z(i,j-1) << " 0\n";
            //[-z(i,j) v z(i,j+1) v z(i+1,j) v z(i,j-1) v z(i-1,j)] /
            myfile << -z(i,j) << ' ' << z(i,j+1) << ' ' << z(i+1,j) << ' ' << z(i,j-1) << ' ' << z(i-1,j) << " 0\n";
            //[q(i,j,s) v -z(i,j+1) v z(i,j)] /
            myfile << q(i,j,'s') << ' ' << -z(i,j+1) << ' ' << z(i,j) << " 0\n";
            //[q(i,j,e) v -z(i+1,j) v z(i,j)] /
            myfile << q(i,j,'e') << ' ' << -z(i+1,j) << ' ' << z(i,j) << " 0\n";
            //[q(i,j,n) v -z(i,j-1) v z(i,j)] / 
            myfile << q(i,j,'n') << ' ' << -z(i,j-1) << ' ' << z(i,j) << " 0\n";
            //[q(i,j,w) v -z(i-1,j) v z(i,j)]
            myfile << q(i,j,'w') << ' ' << -z(i-1,j) << ' ' << z(i,j) << " 0\n";
        }
    }
    in.close();
    myfile.close();
    

    return 0;
}