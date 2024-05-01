#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "AltShader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__)) // Macro pour gérer les erreurs OpenGL, à appeler sur chaque fonction OpenGL

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const AltShader& shader) const;
};