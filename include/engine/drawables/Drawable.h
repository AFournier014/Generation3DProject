#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <MathHelper.h>

class Shader;

template <typename T>
class Drawable
{
public:
	using Point3D = Point3D<T>;
	using Mat4 = Mat4<T>;

	~Drawable() = default;
	virtual void update() = 0;
	virtual void render(Shader& shader, const Mat4& VP, const Point3D& cameraPositionWorld) = 0;
};

#endif // !DRAWABLE_H