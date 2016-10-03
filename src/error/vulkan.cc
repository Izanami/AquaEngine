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

Vulkan::Vulkan() {}

Vulkan::Vulkan(Vulkan const& vulkan) : result_(vulkan.result_) {}

Vulkan& Vulkan::operator=(const Vulkan& vulkan) {
    result_ = vulkan.result_;
    return *this;
}

Vulkan::Vulkan(Vulkan&& vulkan) : result_(std::move(vulkan.result_)) {}

Vulkan& Vulkan::operator=(Vulkan&& vulkan) {
    result_ = std::move(vulkan.result_);
    return *this;
}

Vulkan::Vulkan(VkResult result) : result_(result) {}

Vulkan::~Vulkan() {}

VkResult Vulkan::Result() const noexcept { return result_; }

void Vulkan::SetResult(const VkResult result) noexcept {
    result_ = std::move(result);
    if (result < 0)
        SetError();
    else
        SetSuccess();

    message_ = ToString();
}

std::string Vulkan::ToString() noexcept {
    return std::string(ToString(result_));
}

} /* ae::error */
