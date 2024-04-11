cmake_minimum_required(VERSION 3.18)
project(lib)

set(LIB_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/test1.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/file2.cpp
    # Ajoutez d'autres fichiers .cpp ici
)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_library(lib ${LIB_SOURCES})
target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include/lib)
target_link_libraries(lib PRIVATE GLEW::GLEW glfw imgui::imgui)



# Appliquer les options de compilation
if(MSVC)
  target_compile_options(lib PRIVATE /W4 /WX)
else()
  target_compile_options(lib PRIVATE -Wall -Wextra -Werror)
endif()