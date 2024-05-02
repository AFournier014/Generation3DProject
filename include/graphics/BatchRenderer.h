#pragma once

#include <vector>
#include <memory>
#include "Drawable.h"

template <typename T>
class BatchRenderer
{
public:

	void Add(std::unique_ptr<Drawable<T>> drawable)
	{
		m_Drawables.push_back(drawable);
	}

	void Render(const Mat4<T>& VP)
	{
		for (auto& drawable : m_Drawables)
		{
			drawable->Render(VP);
		}
	}

private:
	std::vector<std::unique_ptr<Drawable<T>>> m_Drawables;
};