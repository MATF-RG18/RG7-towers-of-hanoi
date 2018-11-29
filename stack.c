#include "stack.h"

//Stacks initialization
void initialize_stack()
{
    A.id = 'A';
    B.id = 'B';
    C.id = 'C';

    //setting stack tops
    A.top = 0;
    B.top = 0;
    C.top = 0;

    //setting x positions
    A.tower_pos_x = -TOWER_DISTANCE;
    B.tower_pos_x = 0;
    C.tower_pos_x = TOWER_DISTANCE;

    //y position of the first disk on each tower
    A.disk_pos_y[0] = DISK_HEIGHT;
    B.disk_pos_y[0] = DISK_HEIGHT;
    C.disk_pos_y[0] = DISK_HEIGHT;

    //computing disk size depending on number of disks
    float size = DISK_RADIUS + NO_OF_DISKS * 0.1;

    //placing disks to first tower
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

    if(p->top == MAX_DISK_NUM) {
        printf("Error: tower is full\n");
        exit(EXIT_FAILURE);
    }

    p->size[p->top] = size;
    p->disk_pos_y[p->top] = DISK_HEIGHT * (p->top + 1);
    p->top++;
}
