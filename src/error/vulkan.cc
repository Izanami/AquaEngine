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

#include "vulkan.h"

namespace ae::error {

Vulkan::Vulkan(VkResult result, std::shared_ptr<ae::Instance> instance) {
    SetResult(std::move(result));
    SetInstance(std::move(instance));
}

Vulkan::Vulkan() : Vulkan(VK_SUCCESS, nullptr) {}

Vulkan::Vulkan(VkResult result) : Vulkan(result, nullptr) {}

Vulkan::Vulkan(std::shared_ptr<ae::Instance> instance)
    : Vulkan(VK_SUCCESS, instance) {}

Vulkan::Vulkan(Vulkan&& vulkan)
    : result_(std::move(vulkan.result_)),
      instance_(std::move(vulkan.instance_)) {}

Vulkan& Vulkan::operator=(Vulkan&& vulkan) {
    result_ = std::move(vulkan.result_);
    instance_ = std::move(vulkan.instance_);
    return *this;
}

Vulkan::Vulkan(const Vulkan& vulkan)
    : result_(vulkan.result_), instance_(vulkan.instance_) {}

Vulkan& Vulkan::operator=(const Vulkan& vulkan) {
    result_ = vulkan.result_;
    instance_ = vulkan.instance_;
    return *this;
}

Vulkan::~Vulkan() {}

VkResult Vulkan::Result() const noexcept { return result_; }

void Vulkan::SetResult(const VkResult result) noexcept {
    result_ = std::move(result);
    if (result < 0)
        flags_.SetError();
    else
        flags_.SetSuccess();
}

std::shared_ptr<ae::Instance> Vulkan::Instance() const noexcept {
    return instance_;
}

void Vulkan::SetInstance(std::shared_ptr<ae::Instance> instance) noexcept {
    instance_ = std::move(instance);
}

std::pair<std::string, Flags> Vulkan::DiagnosticAll() noexcept {
    if (result_ == VK_ERROR_EXTENSION_NOT_PRESENT)
        return DiagnosticExtensions();

    return std::make_pair(ToString(), flags_);
}

std::pair<std::string, Flags> Vulkan::DiagnosticExtensions() noexcept {
    auto missing_extensions = Instance()->MissingExtensions();
    std::string error_message(ToString());

    if (missing_extensions.size() > 0) {
        error_message = ToString(VK_ERROR_EXTENSION_NOT_PRESENT);
        flags_.SetError();
        result_ = VK_ERROR_EXTENSION_NOT_PRESENT;
        error_message += " :";
        for (const auto& extension : missing_extensions) {
            error_message += " ";
            error_message += extension;
        }
    }

    return std::make_pair(std::move(error_message), flags_);
}

const std::string Vulkan::ToString() const noexcept {
    return std::string(ToString(result_));
}

} /* ae::error */
