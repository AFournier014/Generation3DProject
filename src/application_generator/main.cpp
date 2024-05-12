#include <cstdlib>
#include <memory>
#include "Application.h"

int main() {
	// Création de l'application et lancement de la boucle principale
	if (auto app = std::make_unique<Application>())
		app->Run();
	else
		return EXIT_FAILURE; // Échec de l'allocation de l'application

	return EXIT_SUCCESS;
}