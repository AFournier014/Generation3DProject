cmake_minimum_required(VERSION 3.18)
project(core)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../../include/*.h")

add_library(core ${SOURCE_FILES} ${HEADER_FILES})

macro(GroupSources curdir)
    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
    ${PROJECT_SOURCE_DIR}/${curdir}/* ${PROJECT_SOURCE_DIR}/${curdir}/${curdir}/*)

    foreach(child ${children})

        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(${groupname} FILES
            ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        endif()
    endforeach()
endmacro()

GroupSources(src)

target_include_directories(core PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../../include/
)

find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

target_link_libraries(core PRIVATE GLEW::GLEW glfw imgui::imgui)
target_link_libraries(core PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# Appliquer les options de compilation
if(MSVC)
  target_compile_options(core PRIVATE /W4 /WX)
else()
  target_compile_options(core PRIVATE -Wall -Wextra -Werror)
endif()