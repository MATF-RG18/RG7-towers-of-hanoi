#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <GL/glut.h>

#define POLE_DISTANCE 2.5
#define POLE_RADIUS 0.1
#define DISK_RADIUS 0.15
#define DISK_HEIGHT 0.27
#define MAX_SIZE 100

int NO_OF_DISKS;
float POLE_HEIGHT;

//Structure that keeps informations for each pole
typedef struct _stack {
    int top;					//number of disks
    float size[MAX_SIZE];		//size of each disk
    float pole_pos_x;			//pole position along the X axis
    float disk_pos_y[MAX_SIZE];	//position of each disk along the Y axis
    char id;                    //id of the pole
} Stack;

//Poles A, B and C
Stack A;
Stack B;
Stack C;

//Pointers to the poles used in a disk movement
Stack *src;
Stack *dest;

//Stacks initialization
void initializeStack();

//Pop disk
float pop(Stack *p);

//Push disk
void push(Stack *p, float size);

#endif
