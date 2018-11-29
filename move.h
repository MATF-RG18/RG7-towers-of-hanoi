#ifndef _MOVE_H_
#define _MOVE_H_

#include "stack.h"
#include "algorithm.h"

#define TIMER_ID 0
#define TIMER_INTERVAL 20
#define MAX_SIZE 100

//Move variables
int moving_up;			//Moving disk up
int moving_down;		//Moving disk down
int moving_side;		//Moving left or right
int move_done;			//Move performed, updating stack
int move_ongoing;		//Indicator that disk is moving

float add_xpos;			//Increment of x position while moving disk left or right
float speed;			//Positions increment while moving disks

int move_count;         //Counting number of moves made

void on_timer(int value);

//Setting up selected move
void initialize_move();

//performing the selected move
void perform_move();

//checking if selected move is valid
int is_valid_move();

//Checking if the puzzle is solved
int is_solved();

#endif
