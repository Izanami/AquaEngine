#include "application.h"

namespace ae {
Application::Application() {
    vulkan_info_.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vulkan_info_.pApplicationName = "";
    vulkan_info_.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    vulkan_info_.pEngineName = "AquaEngine";
    vulkan_info_.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    vulkan_info_.apiVersion = VK_API_VERSION_1_0;
}

Application::Application(std::string name, int major, int minor, int patch)
    : Application() {
    Name(name);
    Version(major, minor, patch);
}

Application::~Application() {}

std::string Application::Name() const { return vulkan_info_.pApplicationName; }
void Application::Name(std::string name) {
    vulkan_info_.pApplicationName = name.c_str();
}

int Application::Version() const {
    return static_cast<int>(vulkan_info_.applicationVersion);
}

void Application::Version(int version) {
    vulkan_info_.applicationVersion = static_cast<uint32_t>(version);
}

void Application::Version(int major, int minor, int patch) {
    Version(MakeVersion(major, minor, patch));
}

} /* ae */
