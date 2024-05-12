#ifndef SCENE_H
#define SCENE_H

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void init() = 0; // Initialisation de la sc�ne
	virtual void handleInput() = 0; // Gestion des entr�es
	virtual void update(float deltaTime) = 0; // Mise � jour de la sc�ne
	virtual void render() = 0; // Rendu de la sc�ne

};

#endif // SCENE_H