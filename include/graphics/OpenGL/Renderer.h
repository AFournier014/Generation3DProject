#include <GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__)) // Macro pour gérer les erreurs OpenGL, à appeler sur chaque fonction OpenGL

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);