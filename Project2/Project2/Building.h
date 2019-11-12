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
private:
	GLubyte display_list;   // The display list that does all the work.
    GLuint  texture_obj;    // The object for the grass texture.
    bool    initialized;    // Whether or not we have been initialised.
};