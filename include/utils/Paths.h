#pragma once

#include <string>

//const std::string SHADER_PATH = "../../ressources/shaders/";

#if defined(DEBUG) || defined(_DEBUG)
// Debug Mode
static const std::string SHADER_PATH = "../ressources/shaders/";

#elif defined(RELEASE) || defined(NDEBUG)
// Release Mode
static const std::string SHADER_PATH = "../ressources/shaders/";

#else
// Fallback ou mode par défaut, peut-être pour d'autres configurations ou l'exécutable
static const std::string SHADER_PATH = "shaders/";
#endif