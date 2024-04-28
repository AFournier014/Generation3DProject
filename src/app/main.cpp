#include <SFML/Window.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <graphics/GeometryTypes.h>
#include <utils/MathHelper.h>

constexpr auto windowWidth = 800;
constexpr auto windowHeight = 600;

Mat4<float> InitFirstTriangle()
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

	

	// Points du cube et couleurs associées (en dur)
	Point3D<float> P000 = { -1, -1, -1 }; Point3D<float> P100 = { +1, -1, -1 }; Point3D<float> P010 = { -1, +1, -1 }; Point3D<float> P110 = { +1, +1, -1 };
	Point3D<float> P001 = { -1, -1, +1 }; Point3D<float> P101 = { +1, -1, +1 }; Point3D<float> P011 = { -1, +1, +1 }; Point3D<float> P111 = { +1, +1, +1 };
	Color3<float> c100 = { +1, +0, +0 }; Color3<float> c010 = { +0, +1, +0 }; Color3<float> c001 = { +0, +0, +1 };
	Color3<float> c011 = { +0, +1, +1 }; Color3<float> c101 = { +1, +0, +1 }; Color3<float> c110 = { +1, +1, +0 };
	Point3D<float> nxn = { -1, 0, 0 }; Point3D<float> nyn = { 0, -1, 0 }; Point3D<float> nzn = { 0, 0, -1 };
	Point3D<float> nxp = { +1, 0, 0 }; Point3D<float> nyp = { 0, +1, 0 }; Point3D<float> nzp = { 0, 0, +1 };

	// Vertex du cube
	using vt = Vertex<float>;
	static std::vector<Vertex<float>> points = {
	   vt{P000, nzn, c100}, vt{P100, nzn, c100}, vt{P110, nzn, c100}, vt{P000, nzn, c100}, vt{P110, nzn, c100}, vt{P010, nzn, c100}
	 , vt{P001, nzp, c011}, vt{P101, nzp, c011}, vt{P111, nzp, c011}, vt{P001, nzp, c011}, vt{P111, nzp, c011}, vt{P011, nzp, c011}
	 , vt{P000, nyn, c010}, vt{P100, nyn, c010}, vt{P101, nyn, c010}, vt{P000, nyn, c010}, vt{P101, nyn, c010}, vt{P001, nyn, c010}
	 , vt{P010, nyp, c101}, vt{P110, nyp, c101}, vt{P111, nyp, c101}, vt{P010, nyp, c101}, vt{P111, nyp, c101}, vt{P011, nyp, c101}
	 , vt{P000, nxn, c001}, vt{P010, nxn, c001}, vt{P011, nxn, c001}, vt{P000, nxn, c001}, vt{P011, nxn, c001}, vt{P001, nxn, c001}
	 , vt{P100, nxp, c110}, vt{P110, nxp, c110}, vt{P111, nxp, c110}, vt{P100, nxp, c110}, vt{P111, nxp, c110}, vt{P101, nxp, c110}
	};

	// Création d'un cube (temporaire)
	CubeF cube(points);

	Point3D<float> cameraPosition{ 0.f, 0.f, 0.f };

	auto P = InitFirstTriangle();
	// Fin du code temporaire

	float alpha = 0.f;
	float beta = 0.f;

	sf::Mouse::setPosition({ windowWidth/2, windowHeight/2 }, window); // Centre la souris, c'est degueu a changer
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

		Mat4<float> V = Mat4<float>::RotationX(-beta) * Mat4<float>::RotationY(-alpha);
		auto VP = P * V;

		// Affichage du contenu
		triangle.Update();
		triangle.render(VP);

		cube.Update();
		cube.render(VP, cameraPosition);

		glFlush();

		// Termine la trame en cours (en interne, échange les deux tampons de rendu)
		window.display();
	}

	// Libération des ressources ...

	return EXIT_SUCCESS;
}