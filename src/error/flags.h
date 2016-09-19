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

#ifndef AE_ERROR_FLAGS_H_
#define AE_ERROR_FLAGS_H_

#include <bitset>
namespace ae::error {

// Number of bits in ae::error::Flags
constexpr int CodeFlagsMax = 8;

// Bits positions in ae::error::Flags
enum class CodeFlags { kSuccess = 0, kVerbose };

// Bit state flags of the error
// Example :
/*
    ae::error::Flags flags;
    if(random_number % 2)
        flags.SetError();
 */
struct Flags : public std::bitset<CodeFlagsMax> {
    Flags();
    virtual ~Flags();

    Flags(const Flags &);
    Flags(Flags &&);
    Flags &operator=(const Flags &);
    Flags &operator=(Flags &&);

    void SetSuccess() noexcept;
    void ResetSuccess() noexcept;
    bool IsSuccess() const noexcept;

    void SetError() noexcept;
    void ResetError() noexcept;
    bool IsError() const noexcept;

    void SetVerbose() noexcept;
    void ResetVerbose() noexcept;
    bool IsVerbose() const noexcept;
};

} /* ae::error */

#endif /* AE_ERROR_FLAGS_H_ */
