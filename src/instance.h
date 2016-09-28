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

/// \brief Handle to Vulkan instance.
///
/// Example :
///
/// \code
///    ae::Instance instance;
///
///    std::vector<const char *> extensions = {VK_KHR_SURFACE_EXTENSION_NAME};
///    instance.AddExtensions(extensions);
///
///    instance.Create();
/// \endcode
class Instance {
   public:
    /// Suggest validations layers.
    const std::vector<const char *> kDefaultValidations = {
        "VK_LAYER_LUNARG_standard_validation"};

    /// If true, enable default validations when Create().
    bool enable_default_validations = true;

    //! \{
    Instance();
    virtual ~Instance();

    Instance(const Instance &);
    Instance(Instance &&);
    Instance &operator=(const Instance &);
    Instance &operator=(Instance &&);
    //! \}

    /// Create vulkan instance.
    VkResult Create() noexcept;

    /// Returns a copy extensions.
    std::vector<const char *> extensions() const noexcept;

    /// \brief Add to the list the extensions which will be activated.
    ///
    /// Example
    /// \code
    ///   ae::Instance instance;
    ///   std::vector<const char *> extensions =
    ///   {VK_KHR_SURFACE_EXTENSION_NAME};
    ///   instance.AddExtensions(extensions);
    /// \endcode
    void AddExtensions(
        const std::vector<const char *> & /* List of extensions */) noexcept;

    /// Returns list of available extensions.
    std::vector<VkExtensionProperties> AvailableExtensions() const noexcept;

    /// Returns list of available extenions with only the name.
    std::vector<const char *> AvailableExtensionsName() const noexcept;

    /// \brief What are the missing extensions Vulkan.
    ///
    /// Compare extensions() with AvailableExtensions().
    /// \return String vector
    std::vector<const char *> MissingExtensions() const noexcept;

    ///  Returns a copy validations layers
    std::vector<const char *> validations() const noexcept;

    /// \brief Add to the list validations which will be activated.
    ///
    /// Example
    /// \code
    ///   ae::Instance instance;
    ///   std::vector<const char *> validation =
    ///   {VK_LAYER_LUNARG_standard_validation};
    ///   instance.AddValidations(validation);
    /// \endcode
    void AddValidations(
        const std::vector<const char *> & /* List of validations */) noexcept;

    /// \brief Add suggest validations.
    /// \sa ae::Instance::kDefaultValidations
    void AddDefaultValidations() noexcept;

    /// Returns list of available validations layers.
    std::vector<VkLayerProperties> AvailableValidations() const noexcept;

    /// Returns list of available validations layers with only the name.
    std::vector<const char *> AvailableValidationsName() const noexcept;

    /// \brief What are the missing validations layers Vulkan.
    ///
    /// Compare validations() with AvailableValidations().
    /// \return String vector
    std::vector<const char *> MissingValidations() const noexcept;

   private:
    /// Pointer to vulkan instance. It initialize with Create().
    std::shared_ptr<VkInstance> vk_instance_ = std::make_shared<VkInstance>();

    /// Opaque handle to a instance vulkan object
    std::shared_ptr<VkInstanceCreateInfo> vk_instance_informations_ =
        std::make_shared<VkInstanceCreateInfo>();

    /// Store list Vulkan extensions
    std::vector<const char *> extensions_;

    ///  Store list Vulkan validations layers
    std::vector<const char *> validations_;
};
} /* ae  */

#endif /* AE_INSTANCE_H_ */
