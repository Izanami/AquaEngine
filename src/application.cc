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

#include "application.h"

namespace ae {
Application::Application() {}

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
