#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

unsigned long int nodes_gen;


int manhattan (state_t state){

	char stateA[100];
	sprint_state(stateA,100,&state);
	string vals(stateA);
	std :: istringstream iss(vals);
    string c;
	iss >> c;
	int first;
	int i =0;
	int h = 0;

	while (i < 16){

		if (c == "B"){
			
			if (i == 15) break;
			iss >> c;
			i++;
			continue;

		}

		first = atoi(c.c_str());
		int row1 = first/4;
		int col1 = first%4;
		int row2 = i/4;
		int col2 = i%4;
		h += abs(row1 - row2) + abs(col1 - col2);
		iss >> c;
		i++;

	}

	return h;
}

int aStar (){
	
}