add_executable(app main.cpp)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
target_link_libraries(app PRIVATE lib)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(lib PRIVATE GLEW::GLEW glfw imgui::imgui)
target_link_libraries(lib PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
 
# Appliquer les options de compilation
if(MSVC)
  target_compile_options(app PRIVATE /W4 /WX)
else()
  target_compile_options(app PRIVATE -Wall -Wextra -Werror)
endif()