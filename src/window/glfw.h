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

#ifndef AE_WINDOW_GLFW_H_
#define AE_WINDOW_GLFW_H_

#include "../window.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace ae::window {

/// \brief GLDW display
///
// For more informations view Window class
class GLFW final : public Window {
   public:
    GLFW();
    virtual ~GLFW() = default;

    //! \{
    GLFW(const GLFW &) = delete;
    GLFW &operator=(const GLFW &) = delete;
    GLFW &operator=(GLFW &&) = delete;
    GLFW(GLFW &&);
    //! \}

    /// Poll for currently pending events.
    bool PoolEvent() noexcept override;

    /// Returns list required extensions.
    ///
    /// \sa ae::Instance
    /// \return String vector
    std::vector<const char *> Extensions() const noexcept override;

   private:
    struct window_deleter {
        void operator()(GLFWwindow *ptr);
    };

    std::unique_ptr<GLFWwindow, window_deleter> window_;
};

} /* ae */

#endif /* AE_WINDOW_GLFW_H_ */
