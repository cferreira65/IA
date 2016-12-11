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
                        myfile << -r(i,j,x,y) << ' ' << q(x,y,'n') << ' ' << r(i,j,x,y-1) << " 0\n";
                    }

                    if (x != n){
                        //-r(c,c') v q(c',e) v r(c,c'')
                        myfile << -r(i,j,x,y) << ' ' << q(x,y,'e') << ' ' << r(i,j,x+1,y) << " 0\n";
                    }

                    if (y != m){
                        //-r(c,c') v q(c',s) v r(c,c'')
                        myfile << -r(i,j,x,y) << ' ' << q(x,y,'s') << ' ' << r(i,j,x,y+1) << " 0\n";
                    }

                    if (x-1 != 0){
                        //-r(c,c') v q(c',w) v r(c,c'')
                        myfile << -r(i,j,x,y) << ' ' << q(x,y,'w') << ' ' << r(i,j,x-1,y) << " 0\n";
                    }

                    myfile << "c Tipo 4\n";
                    //-z(c) v -z(c') v r(c,c')
                    myfile << -z(i,j) << ' ' << -z(x,y) << ' ' << r(i,j,x,y) << " 0\n";

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
            myfile << -z(i,j) << ' ' << -q(i,j,'s') << ' ' << -q(i,j,'e') << ' ' << -q(i,j,'n') << ' ' << -q(i,j,'w') << " 0\n";
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

            myfile << "c Tipo 5\n";
            //[-q(i,j,n) v q(i-1,j,n) v q(i-1,j,e) v q(i,j-1,w)] /
            myfile << -q(i,j,'n') << ' ' << q(i-1,j,'n') << ' ' << q(i-1,j,'e') << ' ' << q(i,j-1,'w') << " 0\n";
            //[-q(i,j,n) v q(i+1,j,n) v q(i+1,j,w) v q(i,j-1,e)]
            myfile << -q(i,j,'n') << ' ' << q(i+1,j,'n') << ' ' << q(i+1,j,'w') << ' ' << q(i,j-1,'e') << " 0\n";
            //[-q(i,j,s) v q(i-1,j,s) v q(i-1,j,e) v q(i,j+1,w)] / 
            myfile << -q(i,j,'s') << ' ' << q(i-1,j,'s') << ' ' << q (i-1,j,'e') << ' ' << q(i,j+1,'w') << " 0\n";
            //[-q(i,j,s) v q(i+1,j,s) v q(i+1,j,w) v q(i,j+1,e)]
            myfile << -q(i,j,'s') << ' ' << q(i+1,j,'s') << ' ' << q(i+1,j,'w') << ' ' << q(i,j+1,'e') << " 0\n";
            //[-q(i,j,w) v q(i,j-1,s) v q(i,j-1,w) v q(i-1,j,n)] /
            myfile << -q(i,j,'w') << ' ' << q(i,j-1,'s') << ' ' << q(i,j-1,'w') << ' ' << q(i-1,j,'n') << " 0\n";
            //[-q(i,j,w) v q(i,j+1,n) v q(i,j+1,w) v q(i-1,j,s)]
            myfile << -q(i,j,'w') << ' ' << q(i,j+1,'n') << ' ' << q(i,j+1,'w') << ' ' << q(i-1,j,'s') << " 0\n";
            //[-q(i,j,e) v q(i,j-1,s) v q(i,j-1,e) v q(i+1,j,n)] /
            myfile << -q(i,j,'e') << ' ' << q(i,j-1,'s') << ' ' << q(i,j-1,'e') << ' ' << q(i+1,j,'n') << " 0\n";
            //[-q(i,j,e) v q(i,j+1,n) v q(i,j+1,e) v q(i+1,j,s)]
            myfile << -q(i,j,'e') << ' ' << q(i,j+1,'n') << ' ' << q(i,j+1,'e') << ' ' << q(i+1,j,'s') << " 0\n";
            
        }
    }
 
    myfile << "c Tipo 5\n";
    //[-q(1,1,n) v q(1,1,w)] /\ [-q(1,1,n) v q(2,1,n) v q(2,1,w)]
    myfile << -q(1,1,'n') << ' ' << q(1,1,'w') << " 0\n";
    myfile << -q(1,1,'n') << ' ' << q(2,1,'n') << ' ' << q(2,1,'w') " 0\n";
    //[-q(1,1,w) v q(1,1,n)] /\ [-q(1,1,w) v q(1,2,n) v q(1,2,w)]
    myfile << -q(1,1,'w') << ' ' << q(1,1,'n') << " 0\n";
    myfile << -q(1,1,'w') << ' ' << q(1,2,'n') << ' ' << q(1,2,'w') " 0\n";

    //[-q(1,M,w) v q(1,M,s)] /\ [-q(1,M,w) v q(1,M-1,s) v q(1,M-1,w)]
    myfile << -q(1,m,'w') << ' ' << q(1,m,'s') << " 0\n";
    myfile << -q(1,m,'w') << ' ' << q(1,m-1,'s') << ' ' << q(1,m-1,'w') " 0\n";
    //[-q(1,M,s) v q(1,M,w)] /\ [-q(1,M,s) v q(2,M,s) v q(2,M,w)]
    myfile << -q(1,m,'s') << ' ' << q(1,m,'w') << " 0\n";
    myfile << -q(1,m,'s') << ' ' << q(2,m,'s') << ' ' << q(2,m,'w') " 0\n";
    
    //[-q(N,1,n) v q(N,1,e)] /\ [-q(N,1,n) v q(N-1,1,n) v q(N-1,1,e)]
    myfile << -q(n,1,'n') << ' ' << q(n,1,'e') << " 0\n";
    myfile << -q(n,1,'n') << ' ' << q(n-1,1,'n') << ' ' << q(n-1,1,'e') " 0\n";
    //[-q(N,1,e) v q(N,1,n)] /\ [-q(N,1,e) v q(N,2,n) v q(N,2,e)]
    myfile << -q(n,1,'e') << ' ' << q(n,1,'n') << " 0\n";
    myfile << -q(n,1,'e') << ' ' << q(n,2,'n') << ' ' << q(n,2,'e') " 0\n";
    
    //[-q(N,M,s) v q(N,M,e)] /\ [-q(N,M,s) v q(N-1,M,s) v q(N-1,M,e)]
    myfile << -q(n,m,'s') << ' ' << q(n,m,'e') << " 0\n";
    myfile << -q(n,m,'s') << ' ' << q(n-1,m,'s') << ' ' << q(n-1,m,'e') " 0\n";
    //[-q(N,M,e) v q(N,M,s)] /\ [-q(N,M,e) v q(N,M-1,s) v q(N,M-1,e)]
    myfile << -q(n,m,'e') << ' ' << q(n,m,'s') << " 0\n";
    myfile << -q(n,m,'e') << ' ' << q(n,m-1,'s') << ' ' << q(n,m-1,'e') " 0\n";

    for (int j = 2; j < m; j++ ){
        //[-q(1,j,w) v q(1,j-1,s) v q(1,j-1,w)] /\ [-q(1,j,w) v q(1,j+1,n) v q(1,j+1,w)]
        myfile << -q(1,j,'w') << ' ' << q(1,j-1,'s') << ' ' << q(1,j-1,'w') " 0\n";
        myfile << -q(1,j,'w') << ' ' << q(1,j+1,'n') << ' ' << q(1,j+1,'w') " 0\n";
        //[-q(1,j,n) v q(1,j,w) v q(1,j-1,w)] /\ [-q(1,j,n) v q(1,j,e) v q(2,j,n) v q(1,j-1,e)]
        myfile << -q(1,j,'n') << ' ' << q(1,j,'w') << ' ' << q(1,j-1,'w') " 0\n";
        myfile << -q(1,j,'n') << ' ' << q(1,j,'e') << ' ' << q(2,j,'n') << ' ' << q(1,j-1,'e') << " 0\n";
        //[-q(1,j,e) v q(1,j+1,n) v q(1,j+1,e) v q(2,j,s)] /\ [-q(1,j,e) v q(1,j-1,s) v q(1,j-1,e) v q(2,j,n)]
        myfile << -q(1,j,'e') << ' ' << q(1,j+1,'n') << ' ' << q(1,j+1,'e') << ' ' << q(2,j,'s') << " 0\n";
        myfile << -q(1,j,'e') << ' ' << q(1,j-1,'s') << ' ' << q(1,j-1,'e') << ' ' << q(2,j,'n') << " 0\n";
        //[-q(1,j,s) v q(1,j,w) v q(1,j+1,w)] /\ [-q(1,j,s) v q(1,j,e) v q(2,j,s) v q(1,j+1,e)]
        myfile << -q(1,j,'s') << ' ' << q(1,j,'w') << ' ' << q(1,j+1,'w') " 0\n";
        myfile << -q(1,j,'s') << ' ' << q(1,j,'e') << ' ' << q(2,j,'s') << ' ' << q(1,j+1,'e') << " 0\n";

        //[-q(N,j,e) v q(N,j-1,s) v q(N,j-1,e)] /\ [-q(N,j,e) v q(N,j+1,n) v q(N,j+1,e)]
        myfile << -q(n,j,'e') << ' ' << q(n,j-1,'s') << ' ' << q(n,j-1,'e') " 0\n";
        myfile << -q(n,j,'e') << ' ' << q(n,j+1,'n') << ' ' << q(n,j+1,'e') " 0\n";
        //[-q(N,j,n) v q(N,j,e) v q(N,j-1,e)] /\ [-q(N,j,n) v q(N,j,w) v q(N-1,j,n) v q(N,j-1,w)]
        myfile << -q(n,j,'n') << ' ' << q(n,j,'e') << ' ' << q(n,j-1,'e') " 0\n";
        myfile << -q(n,j,'n') << ' ' << q(n,j,'w') << ' ' << q(n-1,j,'n') << ' ' << q(n,j-1,'w') << " 0\n";
        //[-q(N,j,w) v q(N,j+1,n) v q(N,j+1,w) v q(N-1,j,s)] /\ [-q(N,j,w) v q(N,j-1,s) v q(N,j-1,w) v q(N-1,j,n)]
        myfile << -q(n,j,'w') << ' ' << q(n,j+1,'n') << ' ' << q(n,j+1,'w') << ' ' << q(n-1,j,'s') << " 0\n";
        myfile << -q(n,j,'w') << ' ' << q(n,j-1,'s') << ' ' << q(n,j-1,'w') << ' ' << q(n-1,j,'n') << " 0\n";
        //[-q(N,j,s) v q(N,j,e) v q(N,j+1,e)] /\ [-q(N,j,s) v q(N,j,w) v q(N-1,j,s) v q(N,j+1,w)]
        myfile << -q(n,j,'s') << ' ' << q(n,j,'e') << ' ' << q(n,j+1,'e') " 0\n";
        myfile << -q(n,j,'s') << ' ' << q(n,j,'w') << ' ' << q(n-1,j,'s') << ' ' << q(n,j+1,'w') << " 0\n";

    }

    for (int i = 2; i < n; i++ ){
        //[-q(i,1,n) v q(i-1,1,n) v q(i-1,1,e)] /\ [-q(i,1,n) v q(i+1,1,n) v q(i+1,1,w)]
        myfile << -q(i,1,'n') << ' ' << q(i-1,1,'n') << ' ' << q(i-1,1,'e') " 0\n";
        myfile << -q(i,1,'n') << ' ' << q(i+1,1,'n') << ' ' << q(i+1,1,'w') " 0\n";
        //[-q(i,1,e) v q(i,1,n) v q(i+1,1,n)] /\ [-q(i,1,e) v q(i,1,s) v q(i,2,e) v q(i+1,1,s)]
        myfile << -q(i,1,'e') << ' ' << q(i,1,'n') << ' ' << q(i+1,1,'n') " 0\n";
        myfile << -q(i,1,'e') << ' ' << q(i,1,'s') << ' ' << q(i,2,'e') << ' ' << q(i+1,1,'s') << " 0\n";
        //[-q(i,1,s) v q(i-1,1,e) v q(i-1,1,s) v q(i,2,w)] /\ [-q(i,1,s) v q(i+1,1,w) v q(i+1,1,s) v q(i,2,e)]
        myfile << -q(i,1,'s') << ' ' << q(i-1,1,'e') << ' ' << q(i-1,1,'s') << ' ' << q(i,2,'w') << " 0\n";
        myfile << -q(i,1,'s') << ' ' << q(i+1,1,'w') << ' ' << q(i+1,1,'s') << ' ' << q(1,2,'e') << " 0\n";
        //[-q(i,1,w) v q(i,1,n) v q(i-1,1,n)] /\ [-q(i,1,w) v q(i,2,n) v q(i,2,w) v q(i-1,1,s)]
        myfile << -q(i,1,'w') << ' ' << q(i,1,'n') << ' ' << q(i-1,1,'n') " 0\n";
        myfile << -q(i,1,'w') << ' ' << q(i,2,'n') << ' ' << q(i,2,'w') << ' ' << q(i-1,1,'s') << " 0\n";

        //[-q(i,M,s) v q(i-1,M,s) v q(i-1,M,e)] /\ [-q(i,M,s) v q(i+1,M,s) v q(i+1,M,w)]
        myfile << -q(i,m,'s') << ' ' << q(i-1,m,'s') << ' ' << q(i-1,m,'e') " 0\n";
        myfile << -q(i,m,'s') << ' ' << q(i+1,m,'s') << ' ' << q(i+1,m,'w') " 0\n";
        //[-q(i,M,w) v q(i-1,M,s) v q(i,M,s)] /\ [-q(i,M,w) v q(i-1,M,n) v q(i,M-1,s) v q(i,M-1,w)]
        myfile << -q(i,m,'w') << ' ' << q(i-1,m,'s') << ' ' << q(i,m,'s') " 0\n";
        myfile << -q(i,m,'w') << ' ' << q(i-1,m,'n') << ' ' << q(i,m-1,'s') << ' ' << q(i,m-1,'w') << " 0\n";
        //[-q(i,M,e) v q(i,M,s) v q(i+1,M,s)] /\ [-q(i,M,e) v q(i,M-1,s) v q(i,M-1,e) v q(i+1,M,n)]
        myfile << -q(i,m,'e') << ' ' << q(i,m,'s') << ' ' << q(i+1,m,'s') << " 0\n";
        myfile << -q(i,m,'e') << ' ' << q(i,m-1,'s') << ' ' << q(i,m-1,'e') << ' ' << q(i+1,m,'n') << " 0\n";
        //[-q(i,M,n) v q(i-1,M,e) v q(i-1,M,n) v q(i,M-1,w)] /\ [-q(i,M,n) v q(i+1,M,w) v q(i+1,M,n) v q(i,M-1,e)]
        myfile << -q(i,m,'n') << ' ' << q(i-1,m,'e') << ' ' << q(i-1,m,'n') << ' ' << q(i,m-1,'w') << " 0\n";
        myfile << -q(i,m,'n') << ' ' << q(i+1,m,'w') << ' ' << q(i+1,m,'n') << ' ' << q(i,m-1,'e') << " 0\n";

    }

    in.close();
    myfile.close();
    

    return 0;
}