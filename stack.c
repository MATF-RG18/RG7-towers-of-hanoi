#include "stack.h"

//Stacks initialization
void initializeStack()
{
    A.id = 'A';
    B.id = 'B';
    C.id = 'C';

    //setting stack tops
    A.top = 0;
    B.top = 0;
    C.top = 0;

    //setting x positions
    A.pole_pos_x = -POLE_DISTANCE;
    B.pole_pos_x = 0;
    C.pole_pos_x = POLE_DISTANCE;

    //y position of the first disk on each pole
    A.disk_pos_y[0] = DISK_HEIGHT;
    B.disk_pos_y[0] = DISK_HEIGHT;
    C.disk_pos_y[0] = DISK_HEIGHT;

    //computing disk size depending on number of disks
    float size = DISK_RADIUS + NO_OF_DISKS * 0.1;

    //placing disks to first pole
    for(int i = 0; i < NO_OF_DISKS; i++) {
        push(&A, size);
        size = size - 0.1;
    }
}

//Pop disc
float pop(Stack *p) {

    float temp = p->size[p->top-1];		//size of popped disk
    p->top--;
    return temp;
}

//Push disc
void push(Stack *p, float size) {

    if(p->top == MAX_SIZE-1) {
        printf("Error: pole is full");
        exit(EXIT_FAILURE);
    }

    p->size[p->top] = size;
    p->disk_pos_y[p->top] = DISK_HEIGHT * (p->top + 1);
    p->top++;
}
