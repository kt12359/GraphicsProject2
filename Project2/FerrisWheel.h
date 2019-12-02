#include <Fl/Fl.h>
#include <Fl/gl.h>

class Sweep {
public:
	//Sweep();
	//~Sweep();
	void Initialize();
	void Draw();
	//void drawFace(float x, float y, float z, float depth);
private:
	GLubyte list;
};

class Seat {
public:
	Seat();
	void makeRectPrism(int width, int height);
	void Initialize(float x, float y, float z);
	void Draw();
private:
	GLubyte seatList;
	GLfloat angle;
	Sweep obj;
	float initX;
	float initY;
	float initZ;
};

class Spokes {
public:
	Spokes();
	Spokes(float x, float y, float z);
	//~Spokes();
	void Initialize();
	void Draw();
	void InitSpokePos(int yPos, int zPos);
private:
	GLubyte spokesList;
	Seat seat[12];
	GLfloat angle;
};

class Stand {
public:
	//Stand();
	//~Stand();
	void Initialize();
	void Draw();
private:
	//needs total of 5 cylinders: 1 horizontal, 4 slanted
	GLubyte standList;
	Spokes spokes;
};

class FerrisWheel {
public:
	FerrisWheel();
	void Initialize();
	void Draw();
private:
	Stand stand;
	float prev;
	float rotationAngle;
	Sweep sweep;
};