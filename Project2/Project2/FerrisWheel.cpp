#include "FerrisWheel.h"
#include <FL/glut.h>
#include <GL/glu.h>
#include <math.h>

int refresh = 1;

FerrisWheel::FerrisWheel(){
	prev = 0;
	rotationAngle = 30.0;
}

void FerrisWheel::Initialize() {
	stand.Initialize();
	sweep.Initialize();
}

void FerrisWheel::Draw() {
	stand.Draw();
	sweep.Draw();
}

Spokes::Spokes(){
	angle = 45.0f;
}

void timer(int val){
	glutPostRedisplay();
	glutTimerFunc(refresh, timer, 0);
}

void Spokes::Initialize() {
	spokesList = glGenLists(1);
	float yPos, zPos;
	yPos = zPos = 12.0;
	glNewList(spokesList, GL_COMPILE);
	glColor3f(0.5,0.5,0.5);
	glTranslatef(30.0,-25.0,18.0);
	//make the spokes of the ferris wheel via triangle fan -- these will be rendered as wireframe, so just the outline of the fan
	InitSpokePos(yPos,zPos);
	glTranslatef(6.0,0.0,0.0);
	InitSpokePos(yPos, zPos);
	glEndList();
	//initialize seats with starting position(s)
	seat[0].Initialize(-3.0,yPos*0.0+2.5,zPos+zPos*(1.0/6.0)-0.5);
	seat[1].Initialize(-3.0,yPos*(1.0/2.0)+2.5,zPos-0.5);
	seat[2].Initialize(-3.0,yPos+2.5,zPos*(2.0/3.0)-0.5);
	seat[3].Initialize(-3.0,yPos+yPos*(1.0/4.0)+2.5,zPos*(1.0/6.0)-0.5);
	seat[4].Initialize(-3.0,yPos+2.5,-zPos*(2.0/3.0)-0.5);
	seat[5].Initialize(-3.0,yPos*(1.0/2.0)+2.5,-zPos-0.5);
	seat[6].Initialize(-3.0,yPos*0.0+2.5,-zPos-zPos*(1.0/6.0)-0.5);
	seat[7].Initialize(-3.0,-yPos*(1.0/2.0)+2.5,-zPos-0.5);
	seat[8].Initialize(-3.0,-yPos+2.5,-zPos*(2.0/3.0)-0.5);
	seat[9].Initialize(-3.0,-yPos-yPos*(1.0/4.0)+2.5,zPos*(1.0/6.0)-0.5);
	seat[10].Initialize(-3.0,-yPos+2.5,zPos*(2.0/3.0)-0.5);
	seat[11].Initialize(-3.0,-yPos*(1.0/2.0)+2.5,zPos-0.5);
}

void Spokes::InitSpokePos(int yPos, int zPos){
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0,yPos*0.0,zPos+zPos*(1.0/6.0));
    glVertex3f(0.0,yPos*(1.0/2.0),zPos);
	glVertex3f(0.0,yPos,zPos*(2.0/3.0));
    glVertex3f(0.0,yPos+yPos*(1.0/4.0),zPos*(1.0/6.0));
    glVertex3f(0.0,yPos,-zPos*(2.0/3.0));
    glVertex3f(0.0,yPos*(1.0/2.0),-zPos);
    glVertex3f(0.0,yPos*0.0,-zPos-zPos*(1.0/6.0));
	glVertex3f(0.0,-yPos*(1.0/2.0),-zPos);
    glVertex3f(0.0,-yPos,-zPos*(2.0/3.0));
	glVertex3f(0.0,-yPos-yPos*(1.0/4.0),zPos*(1.0/6.0));
	glVertex3f(0.0,-yPos,zPos*(2.0/3.0));
	glVertex3f(0.0,-yPos*(1.0/2.0),zPos);
	glVertex3f(0.0,0.0,zPos+zPos*(1.0/6.0));
	glEnd();
}

void Spokes::Draw(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-30.0,-25.0,18.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glTranslatef(30.0, 25.0, -18.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glCallList(spokesList);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glTranslatef(0.0,-3.0, 0.0);
	for(int i = 0; i < 12; ++i){
		seat[i].Draw();
	}
	glPopMatrix();
	angle+=0.2;
}

void Stand::Initialize(){
	float base, top, height, slices, stacks;
	base = top = 1.0;
	height = 10.0;
	slices = stacks = 15.0;
	glPushMatrix();
	//generating call list for horizontal  part of stand list
	standList = glGenLists(1);
	glNewList(standList, GL_COMPILE);
	glColor3f(0.6,0.4,0.8);
	GLUquadricObj * quad = gluNewQuadric();
	glTranslatef(-2.0, 0.0, 6.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	//call list for horizontal part of stand set
	gluCylinder(quad, base, top, height, slices, stacks);
	height = 18.0;
	//now the vertical supports
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	glRotatef(15.0, 0.0, 1.0, 0.0);
	glTranslatef(1.0,0.0,-18.0);
	gluCylinder(quad, base, top, height, slices, stacks);
	glTranslatef(17.0,0.0,4.5);
	glRotatef(-30.0, 0.0, 1.0, 0.0);
	gluCylinder(quad, base, top, height, slices, stacks);
	//cylinders provided by opengl are not filled, so adding covers for ends
	/*float inner, outer, loops;
	inner = 0.0;
	outer = 1.0;
	slices = loops = 10.0;
	gluDisk(quad,inner,outer,slices,loops);
	glTranslatef(0.0,8.0,0.0);*/
	glEndList();
	glPopMatrix();
	spokes.Initialize();
}
void Stand::Draw(){
	glPushMatrix();
	glTranslatef(30.0,-25.0,12.0);
	glCallList(standList);
	glPopMatrix();
	spokes.Draw();
}

Seat::Seat(){
	angle = 45.0f;
}

void Seat::Initialize(float x, float y, float z){
	initX = x;
	initY = y;
	initZ = z;
	seatList = glGenLists(1);
	glNewList(seatList,GL_COMPILE);
	makeRectPrism(1,2);
	glEndList();

}

void Seat::Draw() {
	glPushMatrix();
	glTranslatef(initX, initY, initZ);
	glRotatef(angle, 1.0, 0.0, 0.0);
	glCallList(seatList);

	glPopMatrix();
	angle += 0.2;
}

void Seat::makeRectPrism(int height, int width){
	//FRONT
	glColor3f(0.5,0.6,0.8);
	glBegin(GL_QUADS);

	glVertex3f( -width, -width, -height);
	glVertex3f( -width,  width, -height);
	glVertex3f(  width,  width, -height);
	glVertex3f(  width, -width, -height); 

		//BACK
	glVertex3f(  width, -width, height );
	glVertex3f(  width,  width, height );
	glVertex3f( -width,  width, height );
	glVertex3f( -width, -width, height );

	//RIGHT
	glVertex3f( width, -width, -height );
	glVertex3f( width,  width, -height );
	glVertex3f( width,  width,  height );
	glVertex3f( width, -width,  height );

	//LEFT
	glVertex3f( -width, -width,  height );
	glVertex3f( -width,  width,  height);
	glVertex3f( -width,  width, -height );
	glVertex3f( -width, -width, -height );

	//TOP
	glVertex3f(  width,  width,  height );
	glVertex3f(  width,  width, -height );
	glVertex3f( -width,  width, -height );
	glVertex3f( -width,  width,  height );

	glVertex3f(  width, -width, -height );
	glVertex3f(  width, -width,  height );
	glVertex3f( -width, -width,  height );
	glVertex3f( -width, -width, -height );
	glEnd();
}

void Sweep::Initialize(){
	list = glGenLists(1);
	glColor3f(1.0, 1.0, 1.0);
	glNewList(list, GL_COMPILE);
	glBegin(GL_QUADS);
	for(int i = 0; i < 30; ++i){
		glVertex3f(2.0, 0.0+i, 0.0);
		glVertex3f(2.0, 0.0+i, 4.0);
		glVertex3f(2.0, 2.0+i, 2.0);
		glVertex3f(0.0, 0.0+i, 0.0);
		glTranslatef(0.0, 0.1, 0.0);
	}
	glEnd();
	glEndList();
}

void Sweep::Draw(){
	glPushMatrix();
	glCallList(list);
	glPopMatrix();
}