#include "Tree.h"
#include <GL/glu.h>

void Tree::Initialize()
{
	float base = 0.5;
	float top = 0.5;
	float height = 4.0;
	float slices = 15.0; float stacks = 15.0;
	trunkObj.Initialize(base,top,height,slices,stacks);
	base = 2.0;
	top = 0.0;
	height = 7.0;
	slices = stacks = 15.0;
	leavesObj.Initialize(base,top,height,slices,stacks);
}

//Draws a tree
void Tree::Draw()
{
	float ychange = 0.0;
	for(int i = 0; i < 15; ++i)
	{
		glPushMatrix();
		glTranslatef(-35.0,-42.0+ychange,0.0);
		trunkObj.Draw(i);
		if(i%2 == 0)
			glTranslatef(0.0,0.0,4.0);		//shift up so that tree trunk is not covered
		else
			glTranslatef(0.0,0.0,4.0*1.2);
		leavesObj.Draw(i);
		ychange += 6.0;
		glPopMatrix();
	}

}

void Leaves::Draw(int i){
	if(i % 2 == 0)
		glCallList(leavesList[0]);
	else
		glCallList(leavesList[1]);
}

void Leaves::Initialize(float base, float top, float height, float slices, float stacks) {
	index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	glColor3f(0.18824,0.32157,0.12941); //forest green
	GLUquadricObj * cone = gluNewQuadric();
	gluCylinder(cone, base, top, height, slices, stacks);
	glEndList();

	base *= 1.5; top *= 1.5; height *= 1.5;
	glNewList(index+1, GL_COMPILE);
	glColor3f(0.18824,0.32157,0.12941); //forest green
	cone = gluNewQuadric();
	gluCylinder(cone, base, top, height, slices, stacks);
	glEndList();
	leavesList[0] = index;
	leavesList[1] = index + 1;
}

void Trunk::Draw(int i)
{
	if(i % 2 == 0)
		glCallList(trunkList[0]);
	else
		glCallList(trunkList[1]);
}

void Trunk::Initialize(float base, float top, float height, float slices, float stacks){
	index = glGenLists(1);
	glNewList(index, GL_COMPILE);
	glColor3f(0.38039,0.32157,0.23529); //brown
	GLUquadricObj* cyl = gluNewQuadric();
	gluCylinder(cyl, base, top, height, slices, stacks);
	glEndList();

	base *= 1.2; top *= 1.2; height *= 1.2;
	glNewList(index + 1, GL_COMPILE);
	glColor3f(0.38039,0.32157,0.23529); //brown
	cyl = gluNewQuadric();
	gluCylinder(cyl, base, top, height, slices, stacks);
	glEndList();

	trunkList[0] = index;
	trunkList[1] = index + 1;
}