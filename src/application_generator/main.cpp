#include <cstdlib>
#include <memory>
#include "Application.h"

int main()
{
    // Cr�ation de l'application et lancement de la boucle principale
    if (auto app = std::make_unique<Application>())
        app->Run();
    else
        return EXIT_FAILURE; // �chec de l'allocation de l'application

    return EXIT_SUCCESS;
}
