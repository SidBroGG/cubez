#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init glfw lib");
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "New window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}
