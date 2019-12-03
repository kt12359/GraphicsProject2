#include <Fl/Fl.h>
#include <Fl/gl.h>

class Sweep {
public:
	Sweep();
	~Sweep();
	void Initialize();
	void Draw();
	void initParam(float depth);
private:
	GLuint index;
	GLubyte list[3];
	bool initialized;
};

class Seat {
public:
	Seat();
	~Seat();
	void makeRectPrism(int width, int height);
	void Initialize(float x, float y, float z);
	void Draw();
private:
	GLubyte seatList;
	GLfloat angle;
	float initX;
	float initY;
	float initZ;
	bool initialized;
};

class Spokes {
public:
	Spokes();
	Spokes(float x, float y, float z);
	~Spokes();
	void Initialize();
	void Draw();
	void InitSpokePos(int x, int y, int z, int radius, int numSides);
private:
	GLubyte spokesList;
	Seat seat[12];
	GLfloat angle;
	bool initialized;
};

class Stand {
public:
	Stand();
	~Stand();
	void Initialize();
	void Draw();
private:
	//needs total of 5 cylinders: 1 horizontal, 4 slanted
	GLubyte standList;
	Spokes spokes;
	bool initialized;
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