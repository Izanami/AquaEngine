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

#include <stdexcept>
#include "application.h"
#include "error/vulkan.h"
#include "window.h"

namespace {
struct DemoApp : public ae::Application {
    DemoApp();
    virtual ~DemoApp();

   protected:
    std::shared_ptr<ae::error::Vulkan> error_vulkan_{
        std::make_shared<ae::error::Vulkan>()};
    std::shared_ptr<ae::Instance> instance_{std::make_shared<ae::Instance>()};
    std::unique_ptr<ae::Window> window_{ae::Window::Create()};
};

DemoApp::DemoApp() : ae::Application() {
    set_name("Demo AquaEngine");
    set_version(1, 0, 0);
    error_vulkan_->set_instance(instance_);
    instance_->AddExtensions(window_->extensions());

    instance_->Create();
    error_vulkan_->set_result(instance_->Create());
    if (error_vulkan_->IsError()) throw error_vulkan_->DiagnosticAll().first;

    while (window_->PoolEvent()) {
    };
}
DemoApp::~DemoApp() {}
}

int main() {
    DemoApp();
    return 0;
}
