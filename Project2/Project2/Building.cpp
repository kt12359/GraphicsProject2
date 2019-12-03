#include "Building.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

Building::Building(){
	initialized = false;
}

Building::~Building(){
	if(initialized){
		for(int i = 0; i < 5; ++i){
			glDeleteLists(roofList[i], 1);
			glDeleteLists(wallsList[i], 1);
		}
	}
}

bool Building::Initialize(void)
{
	float buildingHeight, buildingWidth;
	buildingWidth = 3.0;
	buildingHeight = 9.0;

	initialized = texObj.readInTexture("wall.tga",0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObj.getTexture(0));//GL_TEXTURE_2D, textureObj[0]);
	walls = glGenLists(1);
	for(int i = 0; i < 5; ++i){
		if(i %2 == 0){
			buildingHeight = 9.0;
		}
		else
			buildingHeight = 6.0;
		initialized = InitWalls(buildingWidth, buildingHeight, i);
	}

	for(int i = 0; i < 5; ++i){
		wallsList[i] = walls+i;
	}
	glDisable(GL_TEXTURE_2D);

	initialized = texObj.readInTexture("roof.tga",1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObj.getTexture(1));
	roof = glGenLists(1);
	for(int i = 0; i < 5; ++i){
		if(i %2 == 0){
			buildingHeight = 9.0;
		}
		else
			buildingHeight = 6.0;
		initialized = InitRoof(buildingWidth, buildingHeight, i);
	}
	
	for(int i = 0; i < 5; ++i){
		roofList[i] = roof+i;
	}
	glDisable(GL_TEXTURE_2D);


	return initialized;
}

bool Building::InitWalls(int buildingWidth, int buildingHeight, int i){

	glNewList(walls+i, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObj.getTexture(0));//textureObj[0]);

		glBegin(GL_QUADS);

		//Front
		glTexCoord2f(-1.0,-1.0);
		glVertex3f( buildingWidth, -buildingWidth, -buildingHeight );
		glTexCoord2f(1.0,-1.0);
		glVertex3f( buildingWidth,  buildingWidth, -buildingHeight );
		glTexCoord2f(-1.0,1.0);
		glVertex3f( buildingWidth,  buildingWidth,  buildingHeight );
		glTexCoord2f(1.0,1.0);
		glVertex3f( buildingWidth, -buildingWidth,  buildingHeight );

	
		//Back
		glTexCoord2f(1.0,1.0);
		glVertex3f( -buildingWidth, -buildingWidth,  buildingHeight );
		glTexCoord2f(-1.0,1.0);
		glVertex3f( -buildingWidth,  buildingWidth,  buildingHeight);
		glTexCoord2f(1.0,-1.0);
		glVertex3f( -buildingWidth,  buildingWidth, -buildingHeight );
		glTexCoord2f(-1.0,-1.0);
		glVertex3f( -buildingWidth, -buildingWidth, -buildingHeight );

		//Right
		glTexCoord2f(-1.0,1.0);
		glVertex3f(  buildingWidth,  buildingWidth,  buildingHeight );
		glTexCoord2f(1.0,-1.0);
		glVertex3f(  buildingWidth,  buildingWidth, -buildingHeight );
		glTexCoord2f(-1.0,-1.0);
		glVertex3f( -buildingWidth,  buildingWidth, -buildingHeight );	
		glTexCoord2f(1.0,1.0);
		glVertex3f( -buildingWidth,  buildingWidth,  buildingHeight );

		//Left
		glTexCoord2f(-1.0,1.0);
		glVertex3f(  buildingWidth, -buildingWidth, -buildingHeight );
		glTexCoord2f(1.0,-1.0);
		glVertex3f(  buildingWidth, -buildingWidth,  buildingHeight );
		glTexCoord2f(-1.0,-1.0);
		glVertex3f( -buildingWidth, -buildingWidth,  buildingHeight );
		glTexCoord2f(1.0,1.0);
		glVertex3f( -buildingWidth, -buildingWidth, -buildingHeight );
		
		glEnd();
		
		glDisable(GL_TEXTURE_2D);
		
		glEndList();
    return true;
}

bool Building::InitRoof(int buildingWidth, int buildingHeight, int i){

	glNewList(roof+i,GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texObj.getTexture(1));


	glBegin(GL_QUADS);

	//Top
	glTexCoord2f(1.0, 1.0);
	glVertex3f(  buildingWidth, -buildingWidth, buildingHeight );
	glTexCoord2f(-1.0, 1.0);
	glVertex3f(  buildingWidth,  buildingWidth, buildingHeight );
	glTexCoord2f(1.0, -1.0);
	glVertex3f( -buildingWidth,  buildingWidth, buildingHeight );
	glTexCoord2f(-1.0,-1.0);
	glVertex3f( -buildingWidth, -buildingWidth, buildingHeight );
	glEnd();
	glDisable(GL_TEXTURE_2D);
    glEndList();

    return true;
}

// Draw just calls the display list we set up earlier.
void
Building::Draw(void)
{
    glPushMatrix();
	glTranslatef(40.0,42.0,0.0);
	for(int i = 0; i < 5; ++i){
		if(i % 2 == 0)
			glTranslatef(0.0,0.0,9.0);
		else
			glTranslatef(0.0,0.0,6.0);
		glCallList(wallsList[i]);
		glCallList(roofList[i]);
			if(i % 2 == 0)
			glTranslatef(0.0,0.0,-9.0);
		else
			glTranslatef(0.0,0.0,-6.0);
		glTranslatef(0.0, -8.0, 0.0);
	}
    glPopMatrix();
}