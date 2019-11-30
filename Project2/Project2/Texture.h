#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

class Texture {
public:
	Texture();
	~Texture();
	bool readInTexture(char filename[], int whichIndex);
	GLuint& getTexture(int whichIndex);
private:
	GLuint texture[2];
	bool initialized;
	int numTextures;
};

#endif