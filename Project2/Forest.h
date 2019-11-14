#include "Node.h"
#include "Tree.h"

class Forest: public Node {
public:
	//void Initialize();
	Forest();
	~Forest();
	void Draw();
protected:
	Tree * trees;
};