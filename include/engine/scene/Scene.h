#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void init() = 0; // Initialisation de la scène
	virtual void handleInput() = 0; // Gestion des entrées
	virtual void update(float deltaTime) = 0; // Mise à jour de la scène
	virtual void render() = 0; // Rendu de la scène

};

#endif // SCENE_H