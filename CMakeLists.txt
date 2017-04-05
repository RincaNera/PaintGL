cmake_minimum_required(VERSION 3.6)
project(PaintGL)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
        ~/bin/glm/
        ~/bin/glfw-3.2.1/include/
        ~/bin/glew-2.0.0/include/
        ~/bin/Simple_OpenGL_Image_Library/src/
)

link_directories(
        ~/bin/glew-2.0.0/build/lib/
        ~/bin/Simple_OpenGL_Image_Library/lib/
)

find_package(OpenGL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGL)

set(ALL_LIBS
        SOIL
        GLEW
        ${OPENGL_LIBRARY}
        )

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/myGLWidget.cpp headers/myGLWidget.h src/myWindow.cpp headers/myWindow.h src/Shader.cpp headers/Shader.h)

add_executable(PaintGL ${SOURCE_FILES})

target_link_libraries(PaintGL
        ${ALL_LIBS}
        Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL
        )