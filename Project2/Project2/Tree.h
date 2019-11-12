#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <Fl/gl.h>

class Tree {
	public:
		//Tree();
		//~Tree();
		void Draw(); //this can be removed from .h once inheritance functionality implemented
		void Initialize();
	protected:
		//void onDraw();
		GLubyte trunkList;	
		GLubyte leavesList;
};
#endif // !_TREE_H_