#include "window.h"

#ifdef GLFW_VERSION_3
#include "window/glfw.h"
#endif

namespace ae {

#ifdef GLFW_VERSION_3
using DefaultWindow = GLFW;
#else
using DefaultWindow = Window;
#endif

std::unique_ptr<Window> Window::Create() noexcept {
    return std::make_unique<DefaultWindow>();
}

bool Window::PoolEvent() noexcept { return false; }

std::vector<const char *> Window::extensions() const noexcept {
    return std::vector<const char *>();
}

} /* ae */
