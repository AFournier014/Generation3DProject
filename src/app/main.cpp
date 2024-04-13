#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <graphics/GeometryTypes.h>

Mat4<float> InitFirstTriangle() {
	Mat4<float> M;
	Mat4<float> V;
	Mat4<float> P;

	P = Mat4<float>::Identity();

	float aspect = 1.0f;
	float fov = 45.0f / 180.0f * 3.141592f;
	float n = 0.01f;
	float f = 100.0f;

	P(0, 0) = 1.0f / (aspect * std::tan(fov / 2.0f));
	P(1, 1) = 1.0f / std::tan(fov / 2.0f);
	P(2, 2) = -(f + n) / (n - f);
	P(2, 3) = -(2.0f * f * n) / (f - n);
	P(3, 2) = -1.0f;

	V = Mat4<float>::Identity();
	M = Mat4<float>::Identity();

	auto MVP = P * V * M;
	MVP = P;

	return MVP;
}

int main() {
	// J'ai pas bien compris ce que ça fait
	const sf::ContextSettings contextSettings(24, 8, 4, 4, 6);

	// Mise en place d'une fenêtre de rendu SFML
	sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, contextSettings);
	window.setVerticalSyncEnabled(true);

	// Activation de la fenêtre
	window.setActive(true);

	// Lignes de code pour initialiser GLEW (apparemment c'est nécessaire)
	glewExperimental = GL_TRUE;
	if (glewInit()) {
		throw std::runtime_error("Failed to initialize GLEW");
	}

	// TODO: Temporaire, à retirer
	using Vertexf = Vertex<float>;
	using Trianglef = Triangle<float>;

	Vertexf p0{ {-0.9f, -0.9f, -5.0f}, {1.0f, 0.0f, 0.0f} };
	Vertexf p1{ {0.9f, -0.9f, -5.0f}, {0.0f, 1.0f, 0.0f} };
	Vertexf p2{ {0.0f, 0.9f, -5.0f}, {0.0f, 0.0f, 1.0f} };

	Trianglef triangle{ p0, p1, p2 };

	auto MVP = InitFirstTriangle();
	// Fin du code temporaire

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
		}

		// Nettoyage de la fenêtre
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Affichage du contenu
		triangle.render(MVP);
		glFlush();

		// Termine la trame en cours (en interne, échange les deux tampons de rendu)
		window.display();
	}

	// Libération des ressources ...

	return EXIT_SUCCESS;
}