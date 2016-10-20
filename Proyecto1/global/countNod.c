/* This program reads a state from stdin and prints out its successors.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

#define  MAX_LINE_LENGTH 999 

unsigned long long int ns[25];
int b;

void DFS (state_t state, int hist, int d ) {

    if (d > b) 
        return;

    // VARIABLES FOR ITERATING THROUGH state's SUCCESSORS
    state_t child;
    ruleid_iterator_t iter; // ruleid_terator_t is the type defined by the PSVN API successor/predecessor iterators.
    int ruleid; // an iterator returns a number identifying a rule
    int aux;

    // LOOP THOUGH THE CHILDREN ONE BY ONE
    init_fwd_iter(&iter, &state);  // initialize the child iterator
    ++ns[d]; 
    while( (ruleid = next_ruleid(&iter)) >= 0 ) {
        if (fwd_rule_valid_for_history(hist,ruleid)) {
            aux = next_fwd_history(hist,ruleid);
            apply_fwd_rule(ruleid, &state, &child);
            DFS (child, aux, d+1);
        }

    }
    //if( childCount == 0 )
    //    printf("Your state has no children.\n");

}

int main(int argc, char **argv ) {
    
    // VARIABLES FOR INPUT
    char str[MAX_LINE_LENGTH + 1];
    ssize_t nchars; 
    state_t state; // state_t is defined by the PSVN API. It is the type used for individual states.

    if (argc != 3){ 
        printf("ERROR, Please enter: ./[Archive] [Depth] [NumFact]\n");
        return -1;
    }
    // READ A LINE OF INPUT FROM stdin
//    printf("Please enter a state followed by ENTER: ");
//    if( fgets(str, sizeof str, stdin) == NULL ) {
//        printf("Error: empty input line.\n");
//        return 0; 
//    }

    int j,num;
	unsigned long long int fact;
    num = atoi(argv[2]);
	fact = 1;
    for(j = 2; j <= num ; j++){
        fact = fact*j;
	}
	printf("El factorial es: %llu \n", fact);

    first_goal_state(&state, &b);

    // CONVERT THE STRING TO A STATE
//    nchars = read_state(str, &state);
//    if( nchars <= 0 ) {
//        printf("Error: invalid state entered.\n");
//        return 0; 
//    }

    b = 2 + atoi(argv[1]);

//    printf("The state you entered is: ");
//    print_state(stdout, &state);
//    printf("\n");

    DFS (state, init_history, 0);

    int i,superado;
	float emp;
    i = 0;
	superado = 0;
	emp = 0;

	printf("Depth		Nodes			Emp.Branching.Factor\n");
    while (i < b-1) {
        //printf("Number of child at deep %d, %d\n",i,ns[i] );		
		emp = (float)ns[i+1]/(float)ns[i];
		printf("%d		%llu			%f\n",i,ns[i],emp);
		if((superado == 0) && (fact < ns[i])){
			superado = i;
		}
        ++i;
    }

	if (superado == 0){
		printf("No se ha superado el número de estados.\n");
	}
	else{
		printf("El numero de estados se supera en el nivel: %d \n", superado);
	}
    return 0;

}

