#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <MathIncludes.h>
#include <memory>

class Shader;

class Drawable
{
public:
	using Vector3f = Vector3D<float>;
	using Mat4f = Mat4<float>;

	virtual ~Drawable() = default;
	virtual void update() = 0;
	virtual void render(std::shared_ptr<Shader> shader) = 0;
	virtual void release() = 0;
};

#endif // !DRAWABLE_H