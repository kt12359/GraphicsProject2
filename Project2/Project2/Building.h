#include <Fl/gl.h>
#include "Texture.h"

class Building {
public:
	//Building();
	~Building();
	bool Initialize();
	void Draw();
	bool InitRoof(int buildingWidth, int buildingHeight, int i);
	bool InitWalls(int buildingWidth, int buildingHeight, int i);

private:
	GLubyte  roofList[5];
	GLubyte wallsList[5];   // The display list that does all the work.
    GLuint  textureObj[2];    // The object for the wall texture.
	GLuint  roof;
	GLuint  walls;
	GLuint  textureRoofObj;
    bool    initialized;    // Whether or not texture has been properly applied/initialized
	Texture texObj;
};