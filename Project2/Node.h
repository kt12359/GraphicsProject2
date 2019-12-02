#include <Fl/Fl.h>
#include <Fl/Fl_Gl_Window.h>
#include <vector>
using namespace std;

class Node {
public:
	void Draw();
	void Initialize();
	void Update();

protected:
	void onDraw();
	vector<Node> children;
}; //all components in world should be derived from this class - Draw method should call pushmatrix() call onDraw, call children's Draw, pushmatrix() pop..pop. (emulate what is already in worldWindow Draw)
//class ReadTexture