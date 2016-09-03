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
#include <string>

namespace ae {
struct Application {
   public:
    Application();
    Application(std::string name, int major = 1, int minor = 0, int patch = 0);
    virtual ~Application();

    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;

    std::string Name() const;
    void Name(std::string);

    int Version() const;
    void Version(int);
    void Version(int major, int minor, int patch);

   private:
    VkApplicationInfo vulkan_info_ = {};
};
} /* ae  */

constexpr int MakeVersion(int major, int minor, int patch) {
    return (((major) << 22) | ((minor) << 12) | (patch));
}

#endif /* AE_APPLICATION_H_ */
