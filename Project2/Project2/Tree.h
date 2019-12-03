#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <Fl/gl.h>

class Leaves {
public:
	Leaves();
	~Leaves();
	void Draw(int i);
	void Initialize(float base, float top, float height, float slices, float stacks);
protected:
	GLuint index;
	GLubyte leavesList[2];
	bool initialized;
};

class Trunk {
public:
	Trunk();
	~Trunk();
	void Draw(int i);
	void Initialize(float base, float top, float height, float slices, float stacks);
protected:
	GLuint index;
	GLubyte trunkList[2];
	bool initialized;
};

class Tree {
	public:
		void Draw(); //this can be removed from .h once inheritance functionality implemented
		void Initialize();
	protected:
		Leaves leavesObj;
		Trunk trunkObj;
};
#endif