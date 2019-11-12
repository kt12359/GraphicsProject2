#include "FerrisWheel.h"

void FerrisWheel::Initialize() {
	spokes.Initialize();
}

void FerrisWheel::Draw() {
	spokes.Draw();
}

void Spokes::Initialize() {
	spokesList = glGenLists(1);
	glColor3f(1.0,0.0,0.0);
	glNewList(spokesList, GL_COMPILE);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0,0.0,3.0);
    glVertex3f(0.0,2.0,3.0);
	glVertex3f(0.0,3.0,2.0);
    glVertex3f(0.0,3.50,0.50);
    glVertex3f(0.0,3.0,-1.0);
    glVertex3f(0.0,2.0,-2.0);
    glVertex3f(0.0,0.0,-2.50);
	glVertex3f(0.0,-2.0,-2.0);
    glVertex3f(0.0,-3.0,-1.0);
	glVertex3f(0.0,0.0,0.0);
	glEnd();
	glEndList();
}

void Spokes::Draw(){
	glPushMatrix();
	glCallList(spokesList);
	glTranslatef(0.0,4.0,0.0);
	glCallList(spokesList);
	glPopMatrix();
}