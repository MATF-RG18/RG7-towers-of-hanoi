#include "draw.h"

extern float add_xpos;

void draw_background() {
    glPushMatrix();

    //Drawing background
    glBindTexture(GL_TEXTURE_2D, bg_tex_name);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(-15, -15, -5);

        glTexCoord2f(1, 0);
        glVertex3f(15, -15, -5);

        glTexCoord2f(1, 1);
        glVertex3f(15, 15, -5);

        glTexCoord2f(0, 1);
        glVertex3f(-15, 15, -5);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);

}

void draw_towers() {

    set_material('t');
	GLUquadricObj *obj = gluNewQuadric();

	//Drawing plarform for towers
	glTranslatef(0, -1, 0);

	glPushMatrix();
	glBegin(GL_QUADS);

		//Front
		glNormal3f(0, 0, 1);
		glVertex3f(-4, -1, 1.5);
		glVertex3f(4, -1, 1.5);
		glVertex3f(4, 0, 1.5);
		glVertex3f(-4, 0, 1.5);

		//Right
		glNormal3f(1, 0, 0);
		glVertex3f(4, -1, -1.5);
		glVertex3f(4, 0, -1.5);
		glVertex3f(4, 0, 1.5);
		glVertex3f(4, -1, 1.5);

		//Back
		glNormal3f(0, 0, -1);
		glVertex3f(-4, -1, -1.5);
		glVertex3f(-4, 0, -1.5);
		glVertex3f(4, 0, -1.5);
		glVertex3f(4, -1, -1.5);

		//Left
		glNormal3f(-1, 0, 0);
		glVertex3f(-4, -1, -1.5);
		glVertex3f(-4, -1, 1.5);
		glVertex3f(-4, 0, 1.5);
		glVertex3f(-4, 0, -1.5);

		//Top
		glNormal3f(0, 1, 0);
		glVertex3f(-4, 0, -1.5);
		glVertex3f(-4, 0, 1.5);
		glVertex3f(4, 0, 1.5);
		glVertex3f(4, 0, -1.5);

		//Bottom
		glNormal3f(0, -1, 0);
		glVertex3f(-4, -1, -1.5);
		glVertex3f(-4, -1, 1.5);
		glVertex3f(4, -1, 1.5);
		glVertex3f(4, -1, -1.5);
	glEnd();

	glPopMatrix();


	//Drawing towers
	glColor3f (0, 0.7, 0.5);
	glPushMatrix();

		//First tower
		glTranslatef(-TOWER_DISTANCE, 0, 0);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			gluCylinder(obj, TOWER_RADIUS, TOWER_RADIUS, TOWER_HEIGHT, 20, 1);
		glPopMatrix();

		//Second tower
		glTranslatef(TOWER_DISTANCE,0,0);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			gluCylinder(obj, TOWER_RADIUS, TOWER_RADIUS, TOWER_HEIGHT, 20, 1);
		glPopMatrix();

		//Third tower
		glTranslatef(TOWER_DISTANCE,0,0);
		glPushMatrix();
			glRotatef(-90,1,0,0);
			gluCylinder(obj, TOWER_RADIUS, TOWER_RADIUS, TOWER_HEIGHT, 20, 1);
		glPopMatrix();
	glPopMatrix();
}

void draw_disks() {

    set_material('d');

	glPushMatrix();
		//Disks on the first tower
		for(int i=0; i<A.top; i++) {
			glPushMatrix();
				if(src == &A && i == A.top - 1)
					glTranslatef(A.tower_pos_x + add_xpos, A.disk_pos_y[i], 0);
				else
					glTranslatef(A.tower_pos_x, A.disk_pos_y[i], 0);
				glRotatef(90, 1, 0, 0);
				glColor3f(1, 1, 1);
				glutSolidTorus(DISK_RADIUS, A.size[i], 20, 20);
			glPopMatrix();
		}

		//Disks on the second tower
		for(int i=0; i<B.top; i++) {
			glPushMatrix();
				if (src == &B && i == B.top - 1)
					glTranslatef(B.tower_pos_x + add_xpos, B.disk_pos_y[i], 0);
				else
					glTranslatef(B.tower_pos_x, B.disk_pos_y[i], 0);
				glRotatef(85, 1, 0, 0);
				glColor3f(1, 1, 1);
				glutSolidTorus(DISK_RADIUS, B.size[i], 20, 20);
			glPopMatrix();
		}

		//Disks on the third tower
		for(int i=0; i<C.top; i++) {
			glPushMatrix();
				if (src == &C && i == C.top - 1)
					glTranslatef(C.tower_pos_x + add_xpos, C.disk_pos_y[i], 0);
				else
					glTranslatef(C.tower_pos_x, C.disk_pos_y[i], 0);
				glRotatef(85, 1, 0, 0);
				glColor3f(1,1,1);
				glutSolidTorus(DISK_RADIUS, C.size[i], 20, 20);
			glPopMatrix();
		}

	glPopMatrix();

}

void set_material(char id) {

    //Material parameters
    GLfloat ambient_coeffs[] = { 0.1, 0.1, 0.1, 1 };
    GLfloat diffuse_coeffs[] = { 0, 0, 0, 1 }; // r g b a
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    //Shininess parameter
    GLfloat shininess = 5;

    switch (id) {
        case 't':
            diffuse_coeffs[0] = 1;
            diffuse_coeffs[1] = 0.88;
            diffuse_coeffs[2] = 0.4;
            break;
        case 'd':
            diffuse_coeffs[0] = 0.2;
            diffuse_coeffs[1] = 0.8;
            diffuse_coeffs[2] = 0.8;
            break;
    }

    //Material
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
