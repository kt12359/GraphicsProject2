#include "FerrisWheel.h"
#include <GL/glu.h>
#include <math.h>

void FerrisWheel::Initialize() {
	spokes.Initialize();
	stand.Initialize();
}

void FerrisWheel::Draw() {
	spokes.Draw();
	stand.Draw();
}

void Spokes::Initialize() {
	spokesList = glGenLists(1);
	float yPos, zPos;
	yPos = zPos = 12.0;
	glNewList(spokesList, GL_COMPILE);
	glColor3f(0.5,0.5,0.5);
	//make the spokes of the ferris wheel via triangle fan -- these will be rendered as wireframe, so just the outline of the fan
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0,yPos*0.0,zPos+zPos*(1.0/6.0));
    glVertex3f(0.0,yPos*(2.0/3.0),zPos);
	glVertex3f(0.0,yPos,zPos*(2.0/3.0));
    glVertex3f(0.0,yPos+yPos*(1.0/6.0),zPos*(1.0/6.0));
    glVertex3f(0.0,yPos,-zPos*(1.0/3.0));
    glVertex3f(0.0,yPos*(2.0/3.0),-zPos*(2.0/3.0));
    glVertex3f(0.0,yPos*0.0,-zPos*(5.0/6.0));
	glVertex3f(0.0,-yPos*(2.0/3.0),-zPos*(2.0/3.0));
    glVertex3f(0.0,-yPos,-zPos*(1.0/3.0));
	glVertex3f(0.0,-yPos-yPos*(1.0/6.0),zPos*(1.0/6.0));
	glVertex3f(0.0,-yPos,zPos*(2.0/3.0));
	glVertex3f(0.0,-yPos*(2.0/3.0),zPos);
	glVertex3f(0.0,0.0,zPos+zPos*(1.0/6.0));
	glEnd();
	glEndList();
}

void Spokes::Draw(){
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glTranslatef(30.0,-25.0,10.0);
	glCallList(spokesList);
	glTranslatef(6.0,0.0,0.0);
	glCallList(spokesList);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glPopMatrix();
}

void Stand::Initialize(){
	float base, top, height, slices, stacks;
	base = top = 1.0;
	height = 8.0;
	slices = stacks = 15.0;
	//generating call list for horizontal  part of stand list
	standList = glGenLists(1);
	glNewList(standList, GL_COMPILE);
	glColor3f(0.5,0.0,0.75);
	GLUquadricObj * quad = gluNewQuadric();
	glRotatef(90.0, 0.0, 1.0, 0.0);
	gluCylinder(quad, base, top, height, slices, stacks);

	//cylinders provided by opengl are not filled, so adding covers for ends
	float inner, outer, loops;
	inner = 0.0;
	outer = 1.0;
	slices = loops = 10.0;
	gluDisk(quad,inner,outer,slices,loops);
	glTranslatef(0.0,8.0,0.0);
	glEndList();
}
void Stand::Draw(){
	glPushMatrix();
	glTranslatef(29.0,-25.0,10.0);
	glCallList(standList);
	glPopMatrix();
}