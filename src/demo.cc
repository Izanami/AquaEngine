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
#include "instance.h"
#include "window.h"

namespace {
struct DemoApp : public ae::Application {
    DemoApp();
    virtual ~DemoApp();
};

DemoApp::DemoApp() : ae::Application() {
    set_name("Demo AquaEngine");
    set_version(1, 0, 0);

    auto window = ae::Window::Create();

    ae::Instance instance;
    instance.AddExtensions(window->Extensions());
    instance.Create();

    while (window->PoolEvent()) {
    };
}
DemoApp::~DemoApp() {}
}

int main() {
    DemoApp();
    return 0;
}
