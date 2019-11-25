#include <Fl/Fl.h>
#include <Fl/gl.h>

class Seat {
public:
	//needs a rectangular prism
	void makeRectPrism(int width, int height);
	void Initialize();
	void Draw();
private:
	//GLubyte seatList[12];
	GLubyte seatList;
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
};

class Spokes {
	//make 2 triangle fans, use transform matrix to move them apart, just need the outline of each triangle, has to be able to rotate
public:
	//Spokes();
	//~Spokes();
	void Initialize();
	void Draw();
private:
	GLubyte spokesList;
};

class FerrisWheel {
public:
	void Initialize();
	void Draw();
private:
	Spokes spokes;
	Stand stand;
	Seat seat;
	float prev;
};