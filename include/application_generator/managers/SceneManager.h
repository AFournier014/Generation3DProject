#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <stack>

class Scene;

class SceneManager
{
public:
	void pushScene(std::unique_ptr<Scene> scene);
	void popScene();
	void changeScene(std::unique_ptr<Scene> scene);
	void update(float deltaTime);
	void render();

private:
	std::stack<std::unique_ptr<Scene>> m_scenes;
};

#endif // SCENE_MANAGER_H