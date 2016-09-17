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

#ifndef AE_ERROR_DIAGNOSTIC_H_
#define AE_ERROR_DIAGNOSTIC_H_

#include <bitset>
namespace ae::error {
constexpr int CodeFlagsMax = 3;
enum class CodeFlags { kSuccess = 0, kVerbose };
struct Flags : public std::bitset<CodeFlagsMax> {
    Flags();
    virtual ~Flags();

    Flags(const Flags &);
    Flags(Flags &&);
    Flags &operator=(const Flags &);
    Flags &operator=(Flags &&);

    void set_success() noexcept;
    void reset_success() noexcept;
    bool is_success() const noexcept;

    void set_error() noexcept;
    void reset_error() noexcept;
    bool is_error() const noexcept;

    void set_verbose() noexcept;
    void reset_verbose() noexcept;
    bool is_verbose() const noexcept;
};

} /* ae::error */

#endif /* AE_ERROR_DIAGNOSTIC_H_ */
