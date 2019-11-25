/*#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "windows.h"
#include <gl/GL.h>
#include <Fl/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>*/
#include <Fl/gl.h>

class Building {
public:
	//Building();
	//~Building();
	bool Initialize();
	void Draw();
	bool InitRoof(int buildingWidth, int buildingHeight, int i);
	bool InitWalls(int buildingWidth, int buildingHeight, int i);
	bool readTexture();

private:
	GLubyte  roofList[5];
	GLubyte wallsList[5];   // The display list that does all the work.
    GLuint  textureObj[2];    // The object for the wall texture.
	GLuint  roof;
	GLuint  walls;
//	GLubyte wallsList[5];
	GLuint  textureRoofObj;
    bool    initialized;    // Whether or not we have been initialised.
};