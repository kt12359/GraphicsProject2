#include "Building.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

bool Building::Initialize(void)
{
	float buildingHeight, buildingWidth;
	buildingWidth = 3.0;
	buildingHeight = 9.0;

	initialized = readTexture();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureObj[0]);
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

	initialized = readTexture();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureObj[1]);
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

bool Building::readTexture(){
	 ubyte   *image_data;
    int	    image_height, image_width;
    // Load the image for the texture.
    if ( ! ( image_data = (ubyte*)tga_load("wall.tga", &image_width, &image_height, TGA_TRUECOLOR_24) ) ) {
		fprintf(stderr, "Building::Initialize: Couldn't load wall.tga\n");
		return false;
	}

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &textureObj[0]);
    glBindTexture(GL_TEXTURE_2D, textureObj[0]);

    // This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    // This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glColor3f(1.0, 1.0, 1.0);

	    if ( ! ( image_data = (ubyte*)tga_load("roof.tga", &image_width, &image_height, TGA_TRUECOLOR_24) ) ) {
		fprintf(stderr, "Building::Initialize: Couldn't load roof.tga\n");
		return false;
	}

    glBindTexture(GL_TEXTURE_2D, textureObj[1]);

    // This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    // This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

}

bool Building::InitWalls(int buildingWidth, int buildingHeight, int i){

	glNewList(walls+i, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureObj[0]);

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

	glBindTexture(GL_TEXTURE_2D, textureObj[1]);


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
	glTranslatef(40.0,35.0,0.0);
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