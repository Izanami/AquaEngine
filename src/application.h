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

#ifndef AE_APPLICATION_H_
#define AE_APPLICATION_H_

#include <vulkan/vulkan.h>
#include <memory>
#include <string>
#include "result/vulkan.h"

namespace ae {

/// Construct an version number.
constexpr int MakeVersion(const int major, const int minor, const int patch) {
    return (((major) << 22) | ((minor) << 12) | (patch));
}

/// \brief Base class to create AquaEngine application
///
///  Example :
///
/// \code
///     class DemoApp : public ae::Application {
///         DemoApp();
///         virtual ~DemoApp();
///
///        protected:
///         ae::window::DefaultWindow window_;
///         std::shared_ptr<ae::Instance> instance_{
///         std::make_shared<ae::Instance>()};
///     };
///
///     DemoApp::DemoApp() : ae::Application() {
///         SetName("Demo AquaEngine");
///         SetVersion(1, 0, 0);
///         instance_->AddExtensions(window_.Extensions());
///
///         auto result = instance_->Create();
///         if (result.IsError()) throw result.Message();
///
///         while (window_.PoolEvent()) {
///         };
///     }
///
///     DemoApp::~DemoApp() {}
/// \endcode
class Application {
   public:
    /// Base populated informations.
    inline static const VkApplicationInfo kDefaultInformations{
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        nullptr,
        "",
        MakeVersion(1, 0, 0),
        "AquaEngine",
        MakeVersion(1, 0, 0),
        VK_API_VERSION_1_0};

    Application();
    virtual ~Application();

    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;
    Application(Application &&) = delete;

    /// Returns a copy of the application name.
    std::string Name() const noexcept;

    /// Set the application name.
    void SetName(std::string) noexcept;

    /// Returns a copy of the application versions.
    int Version() const noexcept;

    /// Set the application version with integer.
    void SetVersion(const int) noexcept;

    /// Helper to set the application version.
    void SetVersion(const int major, const int minor, const int patch) noexcept;

    /// Returns smart-pointer of Vulkan informations.
    const std::shared_ptr<VkApplicationInfo> Informations() const noexcept;

   private:
    std::shared_ptr<VkApplicationInfo> vulkan_info_ =
        std::make_shared<VkApplicationInfo>(kDefaultInformations);
};

} /* ae  */
#endif /* AE_APPLICATION_H_ */
