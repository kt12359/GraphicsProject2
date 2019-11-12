#include <Fl/Fl.h>
#include <Fl/gl.h>

class Seat {
	//needs a rectangular prism
};

class Stand {
	//needs total of 5 cylinders: 1 horizontal, 4 slanted
};

class Spokes {
	//make 2 triangle fans, use transform matrix to move them apart, just need the outline of each triangle, has to be able to rotate
public:
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
	Seat seat;
	Spokes spokes;
	Stand stand;
};