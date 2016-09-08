#include "window.h"

#ifdef GLFW_VERSION_3
#include "window/glfw.h"
#endif

namespace ae {

std::unique_ptr<Window> Window::Create() {
#ifdef GLFW_VERSION_3
    return std::make_unique<GLFW>();
#else
    return std::make_unique<Window>();
#endif
}

bool Window::PoolEvent() { return false; }

std::vector<const char *> Window::Extensions() {
    return std::vector<const char *>();
}

} /* ae */
