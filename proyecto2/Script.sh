#!/bin/bash

if [ $# != 3 ];then
	echo "./Script ./<Program> <Num_Algorithm> <Arch>.txt"
else
	timeout 1m $1 $2 >> $3
fi 
