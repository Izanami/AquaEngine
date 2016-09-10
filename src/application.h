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

namespace ae {

// Shared information for application
//  Example :
//
// struct MyApp : public ae::Application {
//    MyApp();
//    virtual ~MyApp();
// };
//
// MyApp::MyApp() : ae::Application() {
//    set_name("My application");
//    set_version(1, 0, 0);
//    auto window = ae::Window::Create();
//
//    while (window->PoolEvent()) {
//    };
// }
//
// MyApp::~MyApp() {}
//
//
//  MyApp();
//
struct Application {
   public:
    Application();
    virtual ~Application();

    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;
    Application(Application &&) = delete;

    std::string name() const noexcept;
    void set_name(std::string) noexcept;

    int version() const noexcept;
    void set_version(const int) noexcept;
    void set_version(const int major, const int minor,
                     const int patch) noexcept;

    const std::shared_ptr<VkApplicationInfo> informations() const noexcept;

   private:
    std::shared_ptr<VkApplicationInfo> vulkan_info_ = nullptr;
};
} /* ae  */

constexpr int MakeVersion(const int major, const int minor, const int patch) {
    return (((major) << 22) | ((minor) << 12) | (patch));
}

#endif /* AE_APPLICATION_H_ */
