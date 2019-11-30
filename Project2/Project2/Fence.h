#include "Texture.h"

class Fence {
public:
	Fence();
	~Fence();
	void Initialize();
	void Draw();
	void makeRectPrism(int width, int height);
private:
	GLubyte slat;
	GLubyte post;
	Texture texObj;
	bool initialized;
};
