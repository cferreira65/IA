#!/bin/bash

if [ $# != 7 ];then
    echo "./Script <Num_ini> <Num_fin> ./<Program> ../intances/<Arch>.txt <Arch>.csv <Algorithm> <Heurist>"
else
    D=$4
    D=${D:13}
    echo "grupo, algorithm, heuristic, domain, instance, cost, h0, generated, time, gen_per_sec" >> $5
    let _i=1
    ulimit -m 2048000
    while read line
    do
        G="$line"
	if [ \( $1 -le $_i \) -a \( $2 -ge $_i \) ];then
		timeout 5m $3 "$G" $D >> $5
		if [ $? == 124 ];then
			echo "X, $6, $7, $D, \"$line\", na, na, na, na" >> $5 # -----> agregar algoritmo y heuristica utilizada 
		fi			
	fi
	let _i=$_i+1 
    done < $4 
fi 

        


