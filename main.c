#include "stack.h"
#include "draw.h"
#include "move.h"
#include "algorithm.h"
#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

//Callback functions
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);

void set_light();
void init();
void restart();
void undo_move();

void show_message();
//String that keeps the message we want to show on screen;
char message[MAX_SIZE];


int main(int argc, char **argv) {

    //Initializing glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    //Creating window
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Towers of Hanoi");

    //Initializing callback functions
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);

    //Initializing openGL
    glClearColor(0.1, 0.1, 0.1, 0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);


    //Resolving number of disks
    //If the player enters number of disks
    if(argc > 1) {
        int n = atoi(argv[1]);
        if(n > MAX_SIZE) {
            printf("Number of disks must be smaller then %d\n", MAX_SIZE);
            exit(EXIT_FAILURE);
        }
        else {
            NO_OF_DISKS = n;
        }
    }
    //By default, number of disks is 6
    else
        NO_OF_DISKS = 6;


    init();
    glutMainLoop();

    return 0;
}

//initialization of the variables
void init() {

    POLE_HEIGHT = NO_OF_DISKS * DISK_HEIGHT + 1;
    initializeStack();

    //Initializing move variables
    moving_up = 1;	//First, we are moving up
    moving_down = 0;
    moving_side = 0;
    move_done = 0;
    add_xpos = 0.0;
    speed = 0.09;
    move_ongoing = 0; //Initialy, disks are not moving
    move_count = 0;

    hanoi_active = 0; //Solving by algorithm is not active

    message[0] = '\0';

    //Loading background texture
    load_background();
}

void restart() {
    init();
    glutPostRedisplay();
}

static void on_display(void) {

    set_light();

    //Clearing buffers
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Positioning view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        0, 0, 10,
        0, 0, 0,
        0, 1, 0
    );

    draw_background(); //Drawing background
    draw_poles(); //Drawing poles
    draw_disks(); //Drawing disks

    //Printing message to the screen
    show_message();

    //Sending buffer to display
    glutSwapBuffers();
}

void set_light(){

    //Light position
    GLfloat light_position[] = { 5, 5, 5, 0 };

    //Ambient light
    GLfloat ambient_light[] = { 0.1, 0.1, 0.1, 1 };
    //Diffuse light
    GLfloat diffuse_light[] = { 1, 1, 1, 1 };
    //Specular light
    GLfloat specular_light[] = {0.6, 0.6, 0.6, 1 };

    //Setting light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

}

static void on_keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 27: //ESC
            glDeleteTextures(1, &bg_tex_name);
            exit(0);
            break;
        //restart
        case 'R':
        case 'r':
            move_ongoing = 0;
            restart();
            break;
        // Stopping move
        case 'q':
        case 'Q':
            move_ongoing = 0;
            hanoi_active = 0;
            break;
        // Activating solving puzzle by algorithm
        case 'h':
        case 'H':
            restart();
            hanoi_solve();
            break;

        //move from A to B
        case 'a':
            if (!move_ongoing) {
                src = &A;
                dest = &B;
                initialize_move();
            }
            break;
        //move from B to A
        case 'A':
            if (!move_ongoing) {
                src = &B;
                dest = &A;
                initialize_move();
            }
            break;
        //move from A to C
        case 's':
            if (!move_ongoing) {
                src = &A;
                dest = &C;
                initialize_move();
            }
        break;
        //move from C to A
        case 'S':
            if (!move_ongoing) {
                src = &C;
                dest = &A;
                initialize_move();
            }
            break;
        //move from B to C
        case 'd':
            if (!move_ongoing) {
                src = &B;
                dest = &C;
                initialize_move();
            }
            break;
        //move from C to B
        case 'D':
            if (!move_ongoing) {
                src = &C;
                dest = &B;
                initialize_move();
            }
            break;
        case 'u':
        case 'U':
            undo_move();
            break;
    }
}

static void on_reshape(int w, int h) {

    // Setting viewport
    glViewport(0, 0, w, h);
    // Setting projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) w / h, 1, 30);
}

void show_message() {
    char *c;

    glColor3f(1, 1, 1);
    glPushMatrix();
        glTranslatef(-2 ,-2, 5);
        glRasterPos3f(0, 1.5, 0.5);

        for (c=message; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

    glPopMatrix();

    //Printing pole names to the screen
    char letters[] = {'A', 'B', 'C', '\0'};
    float distance =-1.35;

    glPushMatrix();
        for (c=letters; *c != '\0'; c++){
            glRasterPos3f(distance, 0, 5);
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
            distance += 1.3;
        }
    glPopMatrix();
}

void undo_move() {
    Stack *tmp = dest;
    dest = src;
    src = tmp;
    initialize_move();
}