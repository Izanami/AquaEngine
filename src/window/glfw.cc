#include "glfw.h"

#include <iostream>

namespace ae {

GLFW::GLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(
        kWidth, kHeight, "AquaEngine application", nullptr, nullptr);
    window_ = std::unique_ptr<GLFWwindow, window_deleter>(window);
}

GLFW::GLFW(GLFW&& glfw) : window_(std::move(glfw.window_)) {}

bool GLFW::PoolEvent() {
    if (!glfwWindowShouldClose(window_.get())) {
        glfwPollEvents();
        return true;
    } else {
        return false;
    }
}

void GLFW::window_deleter::operator()(GLFWwindow* ptr) {
    glfwDestroyWindow(ptr);
}

std::vector<std::string> GLFW::Extensions() {
    uint32_t count = 0;
    const char** extensions = nullptr;
    extensions = glfwGetRequiredInstanceExtensions(&count);

    return std::vector<std::string>(extensions, extensions + count);
}

} /* ae */
