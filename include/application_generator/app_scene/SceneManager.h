#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "scene/Scene.h"
#include <memory>
#include <stack>

class SceneManager
{
public:
	void pushScene(std::unique_ptr<Scene> scene);
	void popScene();
	void changeScene(std::unique_ptr<Scene> scene);
	void handleInput();
	void update(float deltaTime);
	void render();

private:
	std::stack<std::unique_ptr<Scene>> m_scenes;
};

#endif // SCENE_MANAGER_H