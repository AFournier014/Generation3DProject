#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>

class Shader;

class Drawable
{
public:
	virtual ~Drawable() = default;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void release() = 0;
};

#endif // !DRAWABLE_H