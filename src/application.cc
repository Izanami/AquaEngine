#include "application.h"

namespace ae {
Application::Application() {
    vulkan_info_->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    vulkan_info_->pApplicationName = "";
    vulkan_info_->applicationVersion = VK_MAKE_VERSION(1, 0, 26);
    vulkan_info_->pEngineName = "AquaEngine";
    vulkan_info_->engineVersion = VK_MAKE_VERSION(1, 0, 0);
    vulkan_info_->apiVersion = VK_API_VERSION_1_0;
}

Application::~Application() {}

std::string Application::name() const noexcept {
    return vulkan_info_->pApplicationName;
}

void Application::set_name(std::string name) noexcept {
    vulkan_info_->pApplicationName = name.c_str();
}

int Application::version() const noexcept {
    return static_cast<int>(vulkan_info_->applicationVersion);
}

void Application::set_version(const int version) noexcept {
    vulkan_info_->applicationVersion = static_cast<uint32_t>(version);
}

void Application::set_version(const int major, const int minor,
                              const int patch) noexcept {
    set_version(MakeVersion(major, minor, patch));
}

const std::shared_ptr<VkApplicationInfo> Application::informations() const
    noexcept {
    return vulkan_info_;
}
} /* ae */
