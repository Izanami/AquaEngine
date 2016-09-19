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

// Handle to Vulkan instance.
// Example :
/*
    ae::Instance instance;

    std::vector<const char *> extensions = {VK_KHR_SURFACE_EXTENSION_NAME};
    instance.AddExtensions(extensions);

    instance.Create();
 */
class Instance {
   public:
    // Suggest validations layers
    const std::vector<const char *> kDefaultValidations = {
        "VK_LAYER_LUNARG_standard_validation"};

    // If true, enable default validations when Create();
    bool enable_default_validations = true;

    Instance();
    virtual ~Instance();

    Instance(const Instance &) = delete;
    Instance(Instance &&) = delete;
    Instance &operator=(const Instance &) = delete;
    Instance &operator=(Instance &&) = delete;

    // Create vulkan instance
    VkResult Create() noexcept;

    // Return copy extensions
    std::vector<const char *> extensions() const noexcept;

    // Example
    /*
       ae::Instance instance;
       std::vector<const char *> extensions = {VK_KHR_SURFACE_EXTENSION_NAME};
       instance.AddExtensions(extensions);
     */
    void AddExtensions(
        const std::vector<const char *> & /* List of extensions */) noexcept;

    // Returns list of available extensions.
    std::vector<VkExtensionProperties> AvailableExtensions() const noexcept;

    // Returns list of available extenions with only the name.
    std::vector<const char *> AvailableExtensionsName() const noexcept;

    // What are the missing extensions Vulkan.
    // Compare extensions() with AvailableExtensions().
    std::vector<const char *> MissingExtensions() const noexcept;

    // Return copy validations layers
    std::vector<const char *> validations() const noexcept;

    // Example
    /*
       ae::Instance instance;
       std::vector<const char *> validation =
       {VK_LAYER_LUNARG_standard_validation};
       instance.AddExtensions(validation);
     */
    void AddValidations(
        const std::vector<const char *> & /* List of validations */) noexcept;

    // Add suggest validations.
    // See ae::Instance::kDefaultValidations
    void AddDefaultValidations() noexcept;

    // Returns list of available validations layers.
    std::vector<VkLayerProperties> AvailableValidations() const noexcept;

    // Returns list of available validations layers with only the name.
    std::vector<const char *> AvailableValidationsName() const noexcept;

    // What are the missing validations layers Vulkan.
    // Compare validations() with AvailableValidations().
    std::vector<const char *> MissingValidations() const noexcept;

   private:
    // Pointer to vulkan instance. It initialize with Create().
    std::shared_ptr<VkInstance> vk_instance_ = std::make_shared<VkInstance>();

    // Opaque handle to a instance vulkan object
    std::shared_ptr<VkInstanceCreateInfo> vk_instance_informations_ =
        std::make_shared<VkInstanceCreateInfo>();

    // Store list Vulkan extensions
    std::vector<const char *> extensions_;

    // Store list Vulkan validations layers
    std::vector<const char *> validations_;
};
} /* ae  */

#endif /* AE_INSTANCE_H_ */
