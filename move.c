#include "move.h"

extern char message[MAX_SIZE];

void initialize_move() {
    sprintf(message, "Moving from %c to %c.\n", src->id, dest->id);

    //Checking if the move is valid
    if(!is_valid_move()) {
        return;
    }

    move_count++;

    //Calling timer function
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    move_ongoing = 1;
}

void on_timer(int value) {

    if (value != TIMER_ID)
        return;

    //Performing selected move
    perform_move();

    //Sending new picture to the screen
    glutPostRedisplay();

    //If the move is still active, timer function is called
    if (move_ongoing || hanoi_active) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }

}

void perform_move() {

    //Index of the top disk on the destination pole
    //If the pole is empty, decrementing top would cause error
    int dest_top = (dest->top == 0) ? 0 : dest->top - 1;

    //moving disk up until it reaches top of the pole
    if(moving_up && src->disk_pos_y[src->top -1] <= POLE_HEIGHT + DISK_HEIGHT/2) {
        src->disk_pos_y[src->top -1] = src->disk_pos_y[src->top -1] + speed;
        if(src->disk_pos_y[src->top -1] > POLE_HEIGHT + DISK_HEIGHT/2) {
            moving_up = 0;
            moving_side = 1;
        }
    }

    //moving disk from left to right until it reaches position of the destination pole
    if(moving_side && src->pole_pos_x < dest->pole_pos_x) {
        add_xpos = add_xpos + speed;

        if(src->pole_pos_x + add_xpos >= dest->pole_pos_x) {
            moving_side = 0;
            moving_down = 1;
        }
    }

    //moving disk from right to left until it reaches position of the destination pole
    else if(moving_side && src->pole_pos_x > dest->pole_pos_x) {
        add_xpos = add_xpos - speed;

        if(src->pole_pos_x + add_xpos <= dest->pole_pos_x) {
            moving_side = 0;
            moving_down = 1;
        }
    }

    //moving disk down until it reaches disk on top
    if(moving_down && src->disk_pos_y[src->top - 1] > dest->disk_pos_y[dest_top] + DISK_HEIGHT/2) {
        src->disk_pos_y[src->top - 1] = src->disk_pos_y[src->top - 1] - speed;

        if(src->disk_pos_y[src->top - 1] <= dest->disk_pos_y[dest_top] + DISK_HEIGHT/2){
            moving_down = 0;
            move_done = 1;
        }
    }

    //move is performed, updating stacks and initializing next move
    if(move_done) {
        push(dest, pop(src));
        moving_up = 1;
        move_done = 0;
        add_xpos = 0.0;
        message[0] = '\0';

        //if solving by algorithm is active we go to the next move in array hanoi_moves
        if(hanoi_active) {
            if(hanoi_counter == m-1) {
                //all moves are performed
                hanoi_active = 0;
                sprintf(message, "Solved in %d moves!", m);
                return;
            }
            hanoi_counter++;
            src = hanoi_moves[hanoi_counter].h_src;
            dest = hanoi_moves[hanoi_counter].h_dest;
        }
        //if human player is solving the puzzle, we wait for the next move
        else
            move_ongoing = 0;

        if(is_solved()) {
            sprintf(message, "Congratulations! Puzzle is solved in %d moves.\n", move_count);
            return;
        }
    }
}

int is_valid_move() {

    //If the moved disk is bigger than the disk on top
    if(dest->top != 0 && src->size[src->top - 1] > dest->size[dest->top - 1]) {
        move_ongoing = 0;
        sprintf(message, "Disk must be smaller then the disk on top\n");
        glutPostRedisplay(); //This is called so that message can be shown
        return 0;
    }

    //If we try to move disk from an empty pole
    if(src->top == 0) {
        sprintf(message, "Source pole is empty.\n");
        glutPostRedisplay();
        return 0;
    }

    return 1;
}

int is_solved() {
    return (C.top == NO_OF_DISKS);
}
