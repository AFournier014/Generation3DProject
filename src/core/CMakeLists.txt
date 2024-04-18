cmake_minimum_required(VERSION 3.18)
project(core)

file(GLOB_RECURSE CPP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB_RECURSE H_HEADER_FILES "${CMAKE_SOURCE_DIR}/include/*")
file(GLOB_RECURSE SHADER_FILES "${CMAKE_SOURCE_DIR}/resources/shaders/*")

add_library(core ${CPP_SOURCE_FILES} ${H_HEADER_FILES} ${SHADER_FILES})

target_include_directories(core PUBLIC "${CMAKE_SOURCE_DIR}/include")

foreach(FILE IN LISTS CPP_SOURCE_FILES H_HEADER_FILES SHADER_FILES)
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    
    # Construire le chemin relatif en fonction du type de fichier
    if("${FILE}" MATCHES "\\.cpp$")
        file(RELATIVE_PATH GROUP "${CMAKE_CURRENT_SOURCE_DIR}" "${PARENT_DIR}")
        set(GROUP "Source Files\\${GROUP}")
    elseif("${FILE}" MATCHES "\\.h$")
        file(RELATIVE_PATH GROUP "${CMAKE_SOURCE_DIR}/include" "${PARENT_DIR}")
        set(GROUP "Header Files\\${GROUP}")
    endif()
    
    # Nettoyer les chemins de groupe pour éliminer les références aux dossiers parents
    string(REPLACE "/../" "\\" GROUP "${GROUP}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    string(REPLACE "../" "" GROUP "${GROUP}") # Enlève les références parentes restantes
    string(REPLACE "\\" "/" GROUP "${GROUP}") # Remet les séparateurs de chemin UNIX pour source_group()

    # Affecter le fichier au groupe dans Visual Studio
    source_group("${GROUP}" FILES "${FILE}")
endforeach()

source_group("Shaders" FILES ${SHADER_FILES})

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(core PRIVATE GLEW::GLEW glfw imgui::imgui)
target_link_libraries(core PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# Inclure les fichiers d'en-tête du projet et les sous dossiers
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include/graphics)
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include/gui)
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include/utils)

# Appliquer les options de compilation
if(MSVC)
  target_compile_options(core PRIVATE /W4 /WX)
else()
  target_compile_options(core PRIVATE -Wall -Wextra -Werror)
endif()