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

#ifndef AE_INSTANCE_H_
#define AE_INSTANCE_H_

#include <vulkan/vulkan.h>
#include <memory>
#include <vector>

namespace ae {
class Instance {
   public:
    const std::vector<const char *> kDefaultValidations = {
        "VK_LAYER_LUNARG_standard_validation"};

#ifndef NDEBUG
    bool enable_default_validations = false;
#else
    bool enable_default_validations = true;
#endif

    Instance();
    virtual ~Instance();

    Instance(const Instance &) = delete;
    Instance(Instance &&) = delete;
    Instance &operator=(const Instance &) = delete;
    Instance &operator=(Instance &&) = delete;

    VkResult Create() noexcept;

    std::vector<const char *> extensions() const noexcept;
    void AddExtensions(const std::vector<const char *> &) noexcept;
    std::vector<VkExtensionProperties> AvailableExtensions() const noexcept;
    std::vector<const char *> AvailableExtensionsName() const noexcept;
    std::vector<const char *> MissingExtensions() const noexcept;

    std::vector<const char *> validations() const noexcept;
    void AddValidations(const std::vector<const char *> &) noexcept;
    void AddDefaultValidations() noexcept;
    std::vector<VkLayerProperties> AvailableValidations() const noexcept;
    std::vector<const char *> AvailableValidationsName() const noexcept;
    std::vector<const char *> MissingValidations() const noexcept;

   private:
    std::shared_ptr<VkInstance> vk_instance_ = std::make_shared<VkInstance>();
    std::shared_ptr<VkInstanceCreateInfo> vk_instance_informations_ =
        std::make_shared<VkInstanceCreateInfo>();
    std::vector<const char *> extensions_;
    std::vector<const char *> validations_;
};
} /* ae  */

#endif /* AE_INSTANCE_H_ */
