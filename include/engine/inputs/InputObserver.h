#ifndef INPUT_OBSERVER_H
#define INPUT_OBSERVER_H
#include <GLFW/glfw3.h>
// Observer interface
class InputObserver {
public:
    virtual void onKeyPressed(int key, int scancode, int action, int mods) = 0;
	virtual void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void onMouseMoved( double xpos, double ypos) = 0;
	virtual void onScroll(double xoffset, double yoffset) = 0;
};

#endif // !INPUT_OBSERVER_H