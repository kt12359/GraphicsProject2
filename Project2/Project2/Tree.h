#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <Fl/gl.h>

class Leaves {
public:
	void Draw(int i);
	void Initialize(float base, float top, float height, float slices, float stacks);
protected:
	GLuint index;
	GLubyte leavesList[2];
};

class Trunk {
public:
	void Draw(int i);
	void Initialize(float base, float top, float height, float slices, float stacks);
protected:
	GLuint index;
	GLubyte trunkList[2];

};

class Tree {
	public:
		//Tree();
		//~Tree();
		void Draw(); //this can be removed from .h once inheritance functionality implemented
		void Initialize();
	protected:
		//void onDraw();
		//GLubyte trunkList;	
		//GLubyte leavesList;
		Leaves leavesObj;
		Trunk trunkObj;
//		void Initialize(float base, float top, float height, float slices, float stacks);
};
#endif // !_TREE_H_