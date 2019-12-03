#define _USE_MATH_DEFINES
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
	GLfloat x, y, z, radius;
	x = 0; y = 0; z = 0; radius = 14;
	GLfloat doublePi = M_PI * 2.0f;
	GLint numSides;
	numSides = 12;
	spokesList = glGenLists(1);

	glNewList(spokesList, GL_COMPILE);
	glColor3f(0.5,0.5,0.5);
	glTranslatef(30.0,-25.0,18.0);
	//make the spokes of the ferris wheel via triangle fan -- these will be rendered as wireframe, so just the outline of the fan
	InitSpokePos(x,y,z,radius,numSides);
	glTranslatef(6.0,0.0,0.0);
	//glRotatef(180.0, 1.0, 0.0, 0.0);
	InitSpokePos(x,y,z,radius,numSides);
	glEndList();

	glPushMatrix();
	for(int i = 0; i < 12; ++i){
		seat[i].Initialize(x, y + (radius * cos(i * doublePi/numSides)), z + (radius * sin(i*doublePi/numSides)));
	}
	glPopMatrix();
}

void Spokes::InitSpokePos(int x, int y, int z, int radius, int numSides){
	GLfloat doublePi = M_PI * 2.0f;
	GLint numVertices = numSides+2;

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	for(int i = 1; i < numVertices; ++i){
		glVertex3f(x, y + (radius * cos(i * doublePi/numSides)), z + (radius * sin(i*doublePi/numSides)));
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	for(int i = 1; i < numVertices; ++i){
		glVertex3f(x, y - (radius * sin(i * doublePi/numSides)), z - (radius * cos(i*doublePi/numSides)));
	}
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
	//glTranslatef(-4.0,-1.0, 3.0);
	glTranslatef(0.0, 0.0, 0.0);
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
	glRotatef(180.0, 1.0, 0.0, 0.0);
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
	//obj.Initialize();
	makeRectPrism(1,2);
	glEndList();

}

void Seat::Draw() {
	glPushMatrix();
	glTranslatef(initX, initY, initZ);
	glTranslatef(-3.0, 0.0, 0.0);
	glRotatef(-angle, 1.0, 0.0, 0.0);
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

//}

//void Sweep::initParam(float angle){
	float translate = 0.2;
	float lowHeight = 2.0;
	float lowWidth = 3.0;
	float upperHeight = 3.0;
	float upperWidth = 1.0;
	float depth = 5.0;
	int numEdges = 8;

	list = glGenLists(1);
	glColor3f(0.5,0.6,0.8);
	glNewList(list, GL_COMPILE);
	glBegin(GL_QUADS);


		//Bottom left
	glVertex3f(0.0, 0.0, 0.0);
		//Bottom right
	glVertex3f(3.0, 0.0, 0.0);
		//Top right
	glVertex3f(3.0, 0.0, lowHeight);
	//Top left
	glVertex3f(0.0, 0.0, lowHeight);

		//Upper middle left
	glVertex3f(upperWidth, 0.0, lowHeight);
		//Upper middle right
	glVertex3f(upperWidth+1, 0.0, lowHeight);
		//Top middle right
	glVertex3f(upperWidth+1, 0.0, upperHeight);
	//Top middle left
	glVertex3f(upperWidth, 0.0, upperHeight);

	for(float i = 0; i < depth; ++i){
	//edges
		//left bottom face
		glVertex3f(0.0, i, 0.0);
		glVertex3f(0.0, i, lowHeight);
		glVertex3f(0.0, i+1.0, lowHeight);
		glVertex3f(0.0, i+1.0, 0.0);

		//left upper face
		glVertex3f(0.0, i, lowHeight);
		glVertex3f(upperWidth, i, lowHeight);
		glVertex3f(upperWidth, i+1.0, lowHeight);
		glVertex3f(0.0, i+1.0, lowHeight);

		//top left face
		glVertex3f(upperWidth, i, lowHeight);
		glVertex3f(upperWidth, i, upperHeight);
		glVertex3f(upperWidth, i+1.0, upperHeight);
		glVertex3f(upperWidth, i+1.0, lowHeight);

		//top face
		glVertex3f(upperWidth, i, upperHeight);
		glVertex3f(upperWidth+1.0, i, upperHeight);
		glVertex3f(upperWidth+1.0, i+1.0, upperHeight);
		glVertex3f(upperWidth, i+1.0, upperHeight);

		//top right face
		glVertex3f(upperWidth+1.0, i+1.0, lowHeight);
		glVertex3f(upperWidth+1.0, i+1.0, upperHeight);
		glVertex3f(upperWidth+1.0, i, upperHeight);
		glVertex3f(upperWidth+1.0, i, lowHeight);

		//right upper face
		glVertex3f(upperWidth+1.0, i, lowHeight);
		glVertex3f(lowWidth, i, lowHeight);
		glVertex3f(lowWidth, i+1.0, lowHeight);
		glVertex3f(upperWidth+1.0, i+1.0, lowHeight);

		//right bottom face
		glVertex3f(lowWidth, i+1.0, 0.0);
		glVertex3f(lowWidth, i+1.0, lowHeight);
		glVertex3f(lowWidth, i, lowHeight);
		glVertex3f(lowWidth, i, 0.0);

		//bottom face
		glVertex3f(lowWidth, i, 0.0);
		glVertex3f(0.0, i, 0.0);
		glVertex3f(0.0, i+1.0, 0.0);
		glVertex3f(lowWidth, i+1.0, 0.0);

		glTranslatef(0.0, 1.0, 0.0);
	}

			//Bottom left
	glVertex3f(3.0, depth, 0.0);
		//Bottom right
	glVertex3f(0.0, depth, 0.0);
		//Top right
	glVertex3f(0.0, depth, lowHeight);
	//Top left
	glVertex3f(3.0, depth, lowHeight);

	//Upper middle left
	glVertex3f(upperWidth+1.0, depth, lowHeight);
	//Upper middle right
	glVertex3f(upperWidth, depth, lowHeight);
	//Top middle right
	glVertex3f(upperWidth, depth, upperHeight);
		//Top middle left
	glVertex3f(upperWidth+1.0, depth, upperHeight);

	glEnd();
	glEndList();
}


void Sweep::Draw(){
	glPushMatrix();
	glTranslatef(20.0, 0.0, 0.0);
	glCallList(list);
	glPopMatrix();
}