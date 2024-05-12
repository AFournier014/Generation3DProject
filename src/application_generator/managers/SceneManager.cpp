#include "managers/SceneManager.h"
#include "scene/Scene.h"

void SceneManager::pushScene(std::unique_ptr<Scene> scene)
{
	scene->init();
	m_scenes.push(std::move(scene));
}

void SceneManager::popScene()
{
	m_scenes.pop();
}

void SceneManager::changeScene(std::unique_ptr<Scene> scene)
{
	while (!m_scenes.empty())
	{
		m_scenes.pop();
	}
	scene->init();
	m_scenes.push(std::move(scene));
}

void SceneManager::handleInput()
{
	if (!m_scenes.empty())
	{
		m_scenes.top()->handleInput();
	}
}

void SceneManager::update(float deltaTime)
{
	if (!m_scenes.empty())
	{
		m_scenes.top()->update(deltaTime);
	}
}

void SceneManager::render()
{
	if (!m_scenes.empty())
	{
		m_scenes.top()->render();
	}
}
