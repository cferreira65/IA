#!/bin/bash

if [ $# != 2 ];then
    echo "Ingrese:  ./Script <Arch_Input>.txt ./.../PATH/../core/minisat"
else
    make
    while read line
    do  
        L="$line"
        echo $L > arch.txt
        #echo $L\n >> out.cnf
        G=${L[0]}
        echo $G
        F=${L[1]}
        #echo $F
        ./encode arch.txt
        $2 encode.cnf solSat.cnf
        ./decode solSat.cnf $G $F 
    done < $1 
fi 

