#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "stack.h"


//Structure that keeps track of moves made by solving algorithm
typedef struct _hmove {
    Stack *h_src;
    Stack *h_dest;
} Hmove;

//Array for storing all moves made by solving algorithm
Hmove hanoi_moves[MAX_SIZE];

//Indicator that solving by algorithm is active
int hanoi_active;
//moves counters
int m;
int hanoi_counter;


void hanoi_solve();

//function that solves towers of hanoi and stores moves in hanoi_moves[] array
void hanoi_alg(int n, Stack *start, Stack *finish, Stack *spare);

#endif
