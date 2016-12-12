/*
Inteligencia Artificial CI-5437
Proyecto 3
Integrantes:
Chiseng Ng Yu               09-11245
María Lourdes Garcia Florez 10-10264
Carlos Ferreira             11-10323

Programa usado para decodificar las salidas de las clausulas respectivas en
formato CNF, arrojados por el sat-solver, de modo que la respuesta sea 
presentada en el formato dentro del archivo out.txt
*/
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in (argv[1]);
    ofstream out ;
    out.open("out.txt", std::ios::app);
    int n = atoi(argv[2]);
    int m = atoi(argv[3]);
    out << n << ' ';
    out << m << ' ';
    string hor[m+1]; // Arreglo de segmentos horizontales
    string ver[n]; // Arreglo de segmentos verticales
    string temp;
    in >> temp;
    int seg;

    if (temp == "UNSAT"){
        out << "UNSAT\n";

        return 0;
    }

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
    out << hor[n]<< "\n";

    in.close();
    out.close();
    
    return 0;
}
