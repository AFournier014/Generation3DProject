#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
<<<<<<< Updated upstream
#include <graphics/GeometryTypes.h>
=======
#include <meshs/simple_shapes/Cube.h>
#include <MathIncludes.h>
#include <Shader.h>
#include <Texture.h>
#include <meshs/simple_shapes/Triangle.h>
#include <Paths.h>
#include <cstdlib>
#include <Camera.h>

>>>>>>> Stashed changes

constexpr auto windowWidth = 800;
constexpr auto windowHeight = 600;

<<<<<<< Updated upstream
Mat4<float> InitFirstTriangle()
{
	using Mat4f = Mat4<float>;

	// Param�tres de la cam�ra, � g�rer autrement
	float aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	float fov = 45.f / 180.f * 3.141592f;
	float n = 0.1f;
	float f = 2.f;

	// Matrice de projection
	Mat4f P = Mat4f::Projection(aspect, fov, n, f);

	return P;
}

=======
>>>>>>> Stashed changes
int main() {
	// J'ai pas bien compris ce que �a fait
	const sf::ContextSettings contextSettings(24, 8, 4, 4, 6);

	// Mise en place d'une fen�tre de rendu SFML
	sf::Window window(sf::VideoMode(windowWidth, windowHeight), "OpenGL", sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);

	// Activation de la fen�tre
	window.setActive(true);

	// Lignes de code pour initialiser GLEW (apparemment c'est n�cessaire)
	glewExperimental = GL_TRUE;
	if (glewInit()) {
		throw std::runtime_error("Failed to initialize GLEW");
	}

	glEnable(GL_DEPTH_TEST); // Activation du test de profondeur, pour g�rer les faces cach�es

	// TODO: Temporaire, � retirer
	using VertexF = Vertex<float>;

	// Cr�ation d'un triangle (temporaire)
	VertexF p0{ {-0.9f, -0.9f, 0.0f}, {-0.9f, 0.9f} };
	VertexF p1{ {0.9f, -0.9f, 0.0f}, {0.9f, 0.9f} };
	VertexF p2{ {0.9f, 0.9f, 0.0f}, {0.9f, -0.9f} };

	Texture texture(TEXTURES_PATH + "texture.png");
	Triangle triangle(p0, p1, p2, texture);

	Shader shader(SHADER_PATH + "cube.vert", SHADER_PATH + "cube.frag");
	Shader shader2(SHADER_PATH + "triangle.vert", SHADER_PATH + "triangle.frag");

	// Cr�ation d'un cube (temporaire)
	Cube cube(Vector3D<float>{0.f, 0.f, -5.f}, 1.f, texture);

<<<<<<< Updated upstream
	auto P = InitFirstTriangle();
	// Fin du code temporaire

	float alpha = 0.f;
	float beta = 0.f;

	sf::Mouse::setPosition({ windowWidth/2, windowHeight/2 }, window); // Centre la souris, c'est degueu a changer
=======
	// Fin du code temporaire

	Vector3D<float> cameraPos(0.f, 0.f, 5.f);

	sf::Mouse::setPosition({ windowWidth / 2, windowHeight / 2 }, window); // Centre la souris, c'est degueu a changer
>>>>>>> Stashed changes
	bool setCameraOn = false; // Pour savoir si on doit bouger la camera
	bool leftMouseButtonPressed = false; // Pour savoir si on doit bouger le cube

	Camera camera(cameraPos);
	camera.InitProjection(static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 45.f / 180.f * 3.141592f, 0.1f, 100.f);

	// Boucle principale
	bool running = true;
	while (running) {
		// Gestion des �v�nements
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// On arr�te le programme
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// On redimensionne le viewport
<<<<<<< Updated upstream
=======
				float aspect = static_cast<float>(event.size.width) / static_cast<float>(event.size.height);
				camera.InitProjection(aspect, 45.f / 180.f * 3.141592f, 0.1f, 100.f);
>>>>>>> Stashed changes
				glViewport(0, 0, event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					running = false;
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					setCameraOn = !setCameraOn;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				float dx = event.mouseMove.x - 400.f;
				float dy = event.mouseMove.y - 300.f;

				sf::Mouse::setPosition({ 400, 300 }, window);

				float coef = 0.001f;

				if (!leftMouseButtonPressed && setCameraOn)
				{
					camera.MouseMoved(Vector2D<float>(dx,dy));
				}
				else
				{
					cube.rotate({ 0.f, 1.f, 0.f }, coef * dx);
					cube.rotate({ 1.f, 0, 0.f }, -coef * dy);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					leftMouseButtonPressed = true;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
					leftMouseButtonPressed = false;
			}
			camera.MouseWheelMoved(event);
		}		
		// Nettoyage de la fen�tre (efface les tampons de couleur et de profondeur)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

<<<<<<< Updated upstream
		Mat4<float> V = Mat4<float>::RotationX(-beta) * Mat4<float>::RotationY(-alpha);
		auto VP = P * V;
=======
		camera.Look();
		camera.Update(GL_TIME_ELAPSED);
		auto VP = camera.GetProjectionViewMatrix();
>>>>>>> Stashed changes

		// Affichage du contenu
		triangle.update();
		triangle.render(shader2, VP, cameraPos);

		cube.update();
		cube.render(shader, VP, cameraPos);

		glFlush();

		// Termine la trame en cours (en interne, �change les deux tampons de rendu)
		window.display();
	}

	// Lib�ration des ressources ...

	return EXIT_SUCCESS;
}