#if defined(_WIN32) && defined(_MSC_VER)
#pragma comment(lib, "glfw3dll.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")
#elif defined(__APPLE__)
#elif defined(__linux__)
#endif

#include <iostream>
#include <fstream>

#include "Window.h"

// Window size
const unsigned int windowWidth = 1280;
const unsigned int windowHeight = 720;

int main()
{
    Window* window = new Window();

    return window->initWindow(windowWidth, windowHeight);
}
