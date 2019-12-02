#include "Fence.h"

Fence::Fence(){
	initialized = false;
}

Fence::~Fence(){
	if(initialized){
		glDeleteLists(slat,1);
	}
}

void Fence::Initialize(){
	//read in wood texture
	initialized = texObj.readInTexture("wood.tga", 0);
	slat = glGenLists(1);
	glNewList(slat, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObj.getTexture(0));
	//make vertical slat
	makeRectPrism(1.0, 3.0);
	glEndList();

	//begin list:
	post = glGenLists(1);
	glNewList(post, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObj.getTexture(0));
	glColor3f(1.0, 1.0, 1.0);
	//make vertical slat
	makeRectPrism(1.0, 3.0);

	//rotate 90 degrees and shift down slightly
	glTranslatef(0.0, 1.5, -0.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	makeRectPrism(1.0, 2.0);
	//end list
	glEndList();

	//turn off texturing
	glDisable(GL_TEXTURE_2D);
}

void Fence::Draw(){
	glPushMatrix();
	glTranslatef(33.0,3.0,3.0);
	for(int i = 0; i < 10; ++i){
		glPushMatrix();
		//call list
		glCallList(post);
		glPopMatrix();
		glTranslatef(0.0, 4.5, 0.0);
		//repeat for entire fence
	}
	glCallList(slat);
	glPopMatrix();
}

void Fence::makeRectPrism(int width, int height){
	//FRONT
	glBegin(GL_QUADS);

	glTexCoord2f(-1.0,-1.0);
	glVertex3f( -width, -width, -height);
	glTexCoord2f(1.0,-1.0);
	glVertex3f( -width,  width, -height);
	glTexCoord2f(-1.0,1.0);
	glVertex3f(  width,  width, -height);
	glTexCoord2f(1.0,1.0);
	glVertex3f(  width, -width, -height); 

	//BACK
	glTexCoord2f(1.0,1.0);
	glVertex3f(  width, -width, height );
	glTexCoord2f(-1.0,1.0);
	glVertex3f(  width,  width, height );
	glTexCoord2f(1.0,-1.0);
	glVertex3f( -width,  width, height );
	glTexCoord2f(-1.0,-1.0);
	glVertex3f( -width, -width, height );

	//RIGHT
	glTexCoord2f(-1.0,1.0);
	glVertex3f( width, -width, -height );
	glTexCoord2f(1.0,-1.0);
	glVertex3f( width,  width, -height );
	glTexCoord2f(-1.0,-1.0);
	glVertex3f( width,  width,  height );
	glTexCoord2f(1.0,1.0);
	glVertex3f( width, -width,  height );

	//LEFT
	glTexCoord2f(-1.0,1.0);
	glVertex3f( -width, -width,  height );
	glTexCoord2f(1.0,-1.0);
	glVertex3f( -width,  width,  height);
	glTexCoord2f(-1.0,-1.0);
	glVertex3f( -width,  width, -height );
	glTexCoord2f(1.0,1.0);
	glVertex3f( -width, -width, -height );

	glTexCoord2f(-1.0,1.0);
	glVertex3f(  width, -width, -height );
	glTexCoord2f(1.0,-1.0);
	glVertex3f(  width, -width,  height );
	glTexCoord2f(-1.0,-1.0);
	glVertex3f( -width, -width,  height );
	glTexCoord2f(1.0,1.0);
	glVertex3f( -width, -width, -height );

	glEnd();
}