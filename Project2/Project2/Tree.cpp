#include "Tree.h"
#include <GL/glu.h>


void Tree::Initialize()
{
	float base = 0.5;
	float top = 0.5;
	float height = 4.0;
	float slices = 15.0; float stacks = 15.0;
	trunkList = glGenLists(1);
	glNewList(trunkList, GL_COMPILE);
	glColor3f(0.38039,0.32157,0.23529); //brown
	GLUquadricObj* cyl = gluNewQuadric();
	gluCylinder(cyl, base, top, height, slices, stacks);
	glEndList();

	leavesList = glGenLists(1);
	glNewList(leavesList, GL_COMPILE);
	glColor3f(0.18824,0.32157,0.12941); //forest green
	base = 2.0;
	top = 0.0;
	height = 7.0;
	slices = stacks = 15.0;
	GLUquadricObj * cone = gluNewQuadric();
	gluCylinder(cone, base, top, height, slices, stacks);
	glEndList();
}

//Draws a tree
void Tree::Draw()
{
	float xchange = 0.0, ychange = 0.0;
	for(int i = 0; i < 10; ++i)
	{
		glPushMatrix();
		glTranslatef(-15.0+xchange,-30.0+ychange,0.0);
		glCallList(trunkList);
		glTranslatef(0.0,0.0,4.0);		//shift up so that tree trunk is not covered
		glCallList(leavesList);
		ychange += 3.0;
		xchange += 5.0;
		glPopMatrix();
	}

}