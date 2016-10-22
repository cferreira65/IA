#!/bin/bash

if [ $# != 5 ];then
    echo "./Script <Num_ini> <Num_fin> ./<Program> ../intances/<Arch>.txt <Arch>.csv"
else
    D=$4
    D=${D:13}
    echo "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec" >> $5
    let _i=1
    while read line
    do 
        G="$line"
	if [ \( $1 -le $_i \) -a \( $2 -ge $_i \) ];then
		timeout 5m $3 "$G" $D >> $5
		if [ $? == 124 ];then
			echo "X, dfid, $D, \"$line\", na, na, na, na" >> $5
		fi			
	fi
	let _i=$_i+1 
    done < $4
fi 


