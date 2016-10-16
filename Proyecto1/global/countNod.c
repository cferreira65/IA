/* This program reads a state from stdin and prints out its successors.

Copyright (C) 2013 by the PSVN Research Group, University of Alberta
*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <sys/time.h>

#define  MAX_LINE_LENGTH 999 

int ns[20];
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
        else {
            apply_fwd_rule(ruleid, &state, &child);
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

    // READ A LINE OF INPUT FROM stdin
    printf("Please enter a state followed by ENTER: ");
    if( fgets(str, sizeof str, stdin) == NULL ) {
        printf("Error: empty input line.\n");
        return 0; 
    }

    // CONVERT THE STRING TO A STATE
    nchars = read_state(str, &state);
    if( nchars <= 0 ) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    b = 5;

    printf("The state you entered is: ");
    print_state(stdout, &state);
    printf("\n");

    DFS (state, init_history, 0);

    int i;
    i = 0;

    while (i < b) {
        printf("Number of child at deep %d, %d\n",i,ns[i] );
        ++i;
    }

    return 0;

}

