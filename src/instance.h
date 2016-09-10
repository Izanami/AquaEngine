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
#include "application.h"

namespace ae {
class Instance final {
   public:
    Instance();
    virtual ~Instance();

    Instance(const Instance &) = delete;
    Instance(Instance &&) = delete;
    Instance &operator=(const Instance &) = delete;
    Instance &operator=(Instance &&) = delete;

    std::shared_ptr<VkInstance> Create();

    void Application(std::shared_ptr<ae::Application>);

    void AddExtensions(std::vector<const char *>);
    std::vector<const char *> Extensions();
    static std::vector<VkExtensionProperties> AvailableExtensions();
    std::vector<const char *> MissingExtensions();

   private:
    std::shared_ptr<VkInstance> vk_instance_ = nullptr;
    std::shared_ptr<VkInstanceCreateInfo> vk_instance_informations_ = nullptr;
    std::shared_ptr<ae::Application> application_ = nullptr;
    std::vector<const char *> extensions_;
};
} /* ae  */

#endif /* AE_INSTANCE_H_ */
