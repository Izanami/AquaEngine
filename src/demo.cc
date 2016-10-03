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
#include "window/detect.h"

namespace {
struct DemoApp : public ae::Application {
    DemoApp();
    virtual ~DemoApp();

   protected:
    ae::error::Vulkan error_vulkan_;
    ae::window::DefaultWindow window_;
    std::shared_ptr<ae::Instance> instance_{std::make_shared<ae::Instance>()};
};

DemoApp::DemoApp() : ae::Application() {
    SetName("Demo AquaEngine");
    SetVersion(1, 0, 0);

    instance_->AddExtensions(window_.Extensions());

    error_vulkan_.SetInstance(instance_);
    error_vulkan_.SetResult(instance_->Create());
    if (error_vulkan_.IsError()) {
        error_vulkan_.DiagnosticAll();
        throw error_vulkan_.Message();
    }

    while (window_.PoolEvent()) {
    };
}
DemoApp::~DemoApp() {}
}

int main() {
    DemoApp();
    return 0;
}
