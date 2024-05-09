#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <MathIncludes.h>

class Shader;

class Drawable
{
public:
	using Point3f = Point3D<float>;
	using Mat4f = Mat4<float>;

	virtual ~Drawable() = default;
	virtual void update() = 0;
	virtual void render(Shader& shader, const Mat4f& VP, const Point3f& cameraPositionWorld) = 0;
};

#endif // !DRAWABLE_H