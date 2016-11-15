#!/bin/bash

if [ $# != 2 ];then
	echo "./Script <Num_Algorithm> <Arch>.txt"
else
	timeout 10m "./main" $1 >> $2
fi 
