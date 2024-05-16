#ifndef CUBE_H
#define CUBE_H

#include "RectangleShape.h"

class Cube : public RectangleShape
{
public:
	explicit Cube(const std::shared_ptr<RenderConfig> renderConfig)
		: RectangleShape(renderConfig)
	{
	}
};

#endif // CUBE_H