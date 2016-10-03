// AquaEngine
// Copyright © 2016 Adrien Jeser <adrien@jeser.me>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "glfw.h"

namespace ae::window {

GLFW::GLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(
        kWidth, kHeight, "AquaEngine application", nullptr, nullptr);
    window_ = std::unique_ptr<GLFWwindow, window_deleter>(window);
}

GLFW::GLFW(GLFW&& glfw) : window_(std::move(glfw.window_)) {}

bool GLFW::PoolEvent() noexcept {
    if (!glfwWindowShouldClose(window_.get())) {
        glfwPollEvents();
        return true;
    }

    return false;
}

void GLFW::window_deleter::operator()(GLFWwindow* ptr) {
    glfwDestroyWindow(ptr);
}

std::vector<const char*> GLFW::extensions() const noexcept {
    uint32_t count = 0;
    const char** extensions = nullptr;
    extensions = glfwGetRequiredInstanceExtensions(&count);

    return std::vector<const char*>(extensions, extensions + count);
}

} /* ae */
