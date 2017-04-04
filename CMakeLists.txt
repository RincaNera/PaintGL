cmake_minimum_required(VERSION 3.6)
project(tuto_opengl)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
        ~/bin/glfw-3.2.1/include/
        ~/bin/glew-2.0.0/include/
)

link_directories(
        ~/bin/glew-2.0.0/build/lib/
)

find_package(OpenGL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui OpenGL)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        glfw3
        Xxf86vm
        Xinerama
        Xcursor
        GLEW
        X11
        pthread
        Xrandr
        Xi
        dl
        rt
        m
        )

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp myGLWidget.cpp myGLWidget.h myWindow.cpp myWindow.h)

add_executable(tuto_opengl ${SOURCE_FILES})

target_link_libraries(tuto_opengl
        ${ALL_LIBS}
        Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL
        )