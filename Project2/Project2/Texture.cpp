#include "Texture.h"

Texture::Texture(){
	initialized = false;
	numTextures = 0;
}

Texture::~Texture(){
	if(initialized){
		for(int i = 0; i < numTextures; ++i)
		{
				glDeleteTextures(1, &texture[i]);
		}
	}
}

GLuint& Texture::getTexture(int whichIndex){
	return texture[whichIndex];
}

bool Texture::readInTexture(char filename[], int whichIndex){

	ubyte   *image_data;
    int	    image_height, image_width;
    // Load the image for the texture.
    if ( ! ( image_data = (ubyte*)tga_load(filename, &image_width, &image_height, TGA_TRUECOLOR_24) ) ) {
		fprintf(stderr, "Building::Initialize: Couldn't load wall.tga\n");
		return false;
	}

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &texture[whichIndex]);
    glBindTexture(GL_TEXTURE_2D, texture[whichIndex]);

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

	initialized = true;
	++numTextures;
}