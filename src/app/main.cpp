#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <graphics/Drawables/Cube.h>
#include <graphics/GeometryTypes.h>

constexpr auto windowWidth = 800;
constexpr auto windowHeight = 600;

Mat4<float> InitProjection()
{
	using Mat4f = Mat4<float>;

	// Paramètres de la caméra, à gérer autrement
	float aspect = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	float fov = 45.f / 180.f * 3.141592f;
	float n = 0.1f;
	float f = 100.f;

	// Matrice de projection
	Mat4f P = Mat4f::Projection(aspect, fov, n, f);

	return P;
}

int main() {
	// J'ai pas bien compris ce que ça fait
	const sf::ContextSettings contextSettings(24, 8, 4, 4, 6);

	// Mise en place d'une fenêtre de rendu SFML
	sf::Window window(sf::VideoMode(windowWidth, windowHeight), "OpenGL", sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);

	// Activation de la fenêtre
	window.setActive(true);

	// Lignes de code pour initialiser GLEW (apparemment c'est nécessaire)
	glewExperimental = GL_TRUE;
	if (glewInit()) {
		throw std::runtime_error("Failed to initialize GLEW");
	}

	glEnable(GL_DEPTH_TEST); // Activation du test de profondeur, pour gérer les faces cachées

	// TODO: Temporaire, à retirer
	using VertexF = Vertex<float>;
	using TriangleF = Triangle<float>;
	using CubeF = Cube<float>;

	// Création d'un triangle (temporaire)
	VertexF p0{ {-0.9f, -0.9f, 0.0f}, {-0.9f, 0.9f} };
	VertexF p1{ {0.9f, -0.9f, 0.0f}, {0.9f, 0.9f} };
	VertexF p2{ {0.9f, 0.9f, 0.0f}, {0.9f, -0.9f} };
	TriangleF triangle{ p0, p1, p2 };

	// Création d'un cube (temporaire)
	CubeF cube(Point3D<float>{0.f, 0.f, 0.f}, 1.f);
	//CubeF cube;

	auto P = InitProjection();
	// Fin du code temporaire

	float alpha = 0.f;
	float beta = 0.f;

	Point3D<float> cameraPos{ 0.f, 0.f, 0.f };

	sf::Mouse::setPosition({ windowWidth / 2, windowHeight / 2 }, window); // Centre la souris, c'est degueu a changer
	bool setCameraOn = false; // Pour savoir si on doit bouger la camera
	bool leftMouseButtonPressed = false; // Pour savoir si on doit bouger le cube

	// Boucle principale
	bool running = true;
	while (running) {
		// Gestion des événements
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// On arrête le programme
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				// On redimensionne le viewport
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
					alpha += coef * dx;
					beta += -coef * dy;
				}
				else
				{
					cube.alpha += coef * dx;
					cube.beta += -coef * dy;
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
		}

		// Nettoyage de la fenêtre (efface les tampons de couleur et de profondeur)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Mat4<float> V = Mat4<float>::RotationX(-beta) * Mat4<float>::RotationY(-alpha) + Mat4<float>::Translation(cameraPos);
		auto VP = P * V;

		// Affichage du contenu
		triangle.Update();
		triangle.render(VP);

		cube.update();
		cube.render(VP, cameraPos);

		glFlush();

		// Termine la trame en cours (en interne, échange les deux tampons de rendu)
		window.display();
	}

	// Libération des ressources ...

	return EXIT_SUCCESS;
}