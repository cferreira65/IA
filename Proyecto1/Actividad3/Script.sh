#!/bin/bash

echo "Introduzca la primera instancia a leer(comienza en 1):"
read A
echo "Introduzca la ultima instancia a leer(termina en 80):"
read B
echo "Introduzca el programa a ejecutar:"
read C
C="./$C"
echo "Introduzca el archivo de instancias a ejecutar:"
read D
F="../instances/$D.txt"
echo "Introduzaca el archivo en donde se va a escribir:"
read E
E="$E.csv"
echo "grupo, algorithm, domain, instance, cost, generated, time, gen_per_sec" >> $E
let _i=1
while read line
G="$line"
do 
	if [ \( $A -le $_i \) -a \( $B -ge $_i \) ];then
		echo -e "$_i ---> $line\n"
		timeout 1 $C $G $D 
		if [ $? == 124 ];then
			echo "X,dfid,$D,\"$line\",na,na,na,na"
		fi			
	fi
	let _i=$_i+1 
done < $F
