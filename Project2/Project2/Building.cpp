#include "Building.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

bool
Building::Initialize(void)
{
    ubyte   *image_data;
    int	    image_height, image_width;

    // Load the image for the texture.
    if ( ! ( image_data = (ubyte*)tga_load("buildingimg.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Building::Initialize: Couldn't load buildingimg.tga\n");
	return false;
    }

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &texture_obj);
    glBindTexture(GL_TEXTURE_2D, texture_obj);

    // This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // ground.
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, 
		      GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_NEAREST_MIPMAP_LINEAR);

    // This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

    // Creating display list
    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);
	// White -- texture supplies color
	glColor3f(1.0, 1.0, 1.0);


	// Turn on texturing and bind the building texture.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	//FRONT
glBegin(GL_POLYGON);

glNormal3f(0.0, 1.0, 0.0);
glTexCoord2f(4.0, 4.0);
glVertex3f( -2.0, -2.0, -4.0);
glVertex3f( -2.0,  2.0, -4.0);
glVertex3f(  2.0,  2.0, -4.0);
glVertex3f(  2.0, -2.0, -4.0); 

glEnd();

	// White side - BACK
glBegin(GL_POLYGON);
glNormal3f(0.0, -1.0, 0.0);
glTexCoord2f(-4.0, -4.0);
glVertex3f(  2.0, -2.0, 4.0 );
glVertex3f(  2.0,  2.0, 4.0 );
glVertex3f( -2.0,  2.0, 4.0 );
glVertex3f( -2.0, -2.0, 4.0 );
glEnd();

// Purple side - RIGHT
glBegin(GL_POLYGON);
glNormal3f(-1.0, 0.0, 0.0);
glTexCoord2f(-4.0, 4.0);
glVertex3f( 2.0, -2.0, -4.0 );
glVertex3f( 2.0,  2.0, -4.0 );
glVertex3f( 2.0,  2.0,  4.0 );
glVertex3f( 2.0, -2.0,  4.0 );
glEnd();

// Green side - LEFT
glBegin(GL_POLYGON);
glNormal3f(1.0, 0.0, 0.0);
glTexCoord2f(4.0, -4.0);
glVertex3f( -2.0, -2.0,  4.0 );
glVertex3f( -2.0,  2.0,  4.0);
glVertex3f( -2.0,  2.0, -4.0 );
glVertex3f( -2.0, -2.0, -4.0 );
glEnd();

// Blue side - TOP
glBegin(GL_POLYGON);
glNormal3f(0.0, 0.0, 1.0);
glTexCoord2f(4.0, 4.0);
glVertex3f(  2.0,  2.0,  4.0 );
glVertex3f(  2.0,  2.0, -4.0 );
glVertex3f( -2.0,  2.0, -4.0 );
glVertex3f( -2.0,  2.0,  4.0 );
glEnd();

	// Turn texturing off again, because we don't want everything else to
	// be textured.
	glDisable(GL_TEXTURE_2D);
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
Building::Draw(void)
{
    glPushMatrix();
    glCallList(display_list);
    glPopMatrix();
}