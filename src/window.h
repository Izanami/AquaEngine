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

#ifndef AE_WINDOW_H_
#define AE_WINDOW_H_

#include <memory>
#include <vector>

namespace ae {

/// \brief Interface class for window display
///
// Use Create() for default behavior
///
/// Example :
///
/// \code
///     auto window = ae::Window::Create();
///     while(window->PoolEvent()) {}
/// \endcode
class Window {
   public:
    /// Default width size window
    const int kWidth = 800;

    /// Default height size window
    const int kHeight = 600;

    Window() = default;
    virtual ~Window() = default;

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = delete;
    Window(Window &&) = delete;

    /// Poll for and process events
    virtual bool PoolEvent() noexcept;

    /// Returns the extensions used
    virtual std::vector<const char *> extensions() const noexcept;
};

} /* ae */

#endif /* AE_WINDOW_H_ */
