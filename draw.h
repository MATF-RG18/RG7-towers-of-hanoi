#ifndef _DRAW_H_
#define _DRAW_H_

#include "stack.h"
#include "image.h"

#include <GL/glut.h>

extern GLuint bg_tex_name;

//Drawing background
void draw_background();

//Drawing poles
void draw_poles();

//Drawing disks
void draw_disks();

//Setting material for objects
void set_material(char id);

#endif
