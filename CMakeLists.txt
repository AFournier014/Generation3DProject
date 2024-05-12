cmake_minimum_required(VERSION 3.18)
project(Generation3DProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Définir le chemin local par défaut de vcpkg par rapport à ce fichier CMakeLists.txt
set(VCPKG_LOCAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg")

# Utiliser VCPKG_ROOT si défini, sinon utiliser le chemin local
if(DEFINED ENV{VCPKG_ROOT})
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "Vcpkg toolchain file")
else()
  set(CMAKE_TOOLCHAIN_FILE "${VCPKG_LOCAL_DIR}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "Vcpkg toolchain file")
endif()

# Vérifier si le fichier de chaîne d'outils vcpkg a été correctement trouvé
if(NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
  message(FATAL_ERROR "CMAKE_TOOLCHAIN_FILE non défini ou chemin invalide : ${CMAKE_TOOLCHAIN_FILE}")
endif()

# Définir les dossiers de sortie des binaires
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Définir les chemins de ressources
set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources")
set(ASSET_DIR "${RESOURCE_DIR}/assets")
set(SHADER_DIR "${RESOURCE_DIR}/shaders")
set(TEXTURE_DIR "${RESOURCE_DIR}/texture")
set(FONT_DIR "${RESOURCE_DIR}/fonts")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Configurer les sous-projets
add_subdirectory(src/engine)
add_subdirectory(src/application_generator)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT application_generator)

