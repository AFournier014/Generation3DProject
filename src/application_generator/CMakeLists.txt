cmake_minimum_required(VERSION 3.18)
project(application_generator)

file(GLOB_RECURSE CPP_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*")
file(GLOB_RECURSE H_HEADER_FILES "${CMAKE_SOURCE_DIR}/include/application_generator/*")

add_executable(application_generator main.cpp ${CPP_SOURCE_FILES} ${H_HEADER_FILES})

target_include_directories(application_generator PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(application_generator PRIVATE engine)

foreach(FILE IN LISTS CPP_SOURCE_FILES H_HEADER_FILES)
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

find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(application_generator PRIVATE GLEW::GLEW imgui::imgui ImGui-SFML::ImGui-SFML)
target_link_libraries(application_generator PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(application_generator PRIVATE glfw)

target_include_directories(application_generator PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(application_generator PRIVATE ${CMAKE_SOURCE_DIR}/include/application_generator)
target_include_directories(application_generator PRIVATE ${CMAKE_SOURCE_DIR}/include/engine)
target_include_directories(application_generator PRIVATE ${CMAKE_SOURCE_DIR}/include/application_generator/application)

file(COPY ${RESOURCE_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set_target_properties(application_generator PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)
 
# Appliquer les options de compilation
if(MSVC)
  target_compile_options(application_generator PRIVATE /W4 /WX)
else()
  target_compile_options(application_generator PRIVATE -Wall -Wextra -Werror)
endif()