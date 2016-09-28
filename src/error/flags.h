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

/// Number of bits in ae::error::Flags.
constexpr int CodeFlagsMax = 8;

/// \brief Bit state flags of the error.
///
/// Example :
///
/// \code
///    ae::error::Flags flags;
///    if(random_number % 2)
///        flags.SetError();
/// \endcode
struct Flags : public std::bitset<CodeFlagsMax> {
   public:
    /// Bits positions in std::bitset.
    enum class Code { kSuccess = 0, kVerbose = 1 };

    /// Base class of ae::error::Flags.
    using base = std::bitset<CodeFlagsMax>;

    Flags();
    virtual ~Flags();

    //! \{
    Flags(const Flags &);
    Flags(Flags &&);
    Flags &operator=(const Flags &);
    Flags &operator=(Flags &&);
    //! \}

    /// Set the kSuccess bit flag to true.
    void SetSuccess() noexcept;

    /// Set the kSuccess bit flag to false.
    void ResetSuccess() noexcept;

    /// Returns the kSuccess bit flag.
    bool IsSuccess() const noexcept;

    /// Alias to ResetSuccess().
    void SetError() noexcept;

    /// Alias to SetSuccess().
    void ResetError() noexcept;

    /// Invert IsSuccess().
    bool IsError() const noexcept;

    /// Set the kVerbose bit flag to true.
    void SetVerbose() noexcept;

    /// Set the kVerbose bit flag to false.
    void ResetVerbose() noexcept;

    /// Returns the kVerbose bit flag.
    bool IsVerbose() const noexcept;
};

} /* ae::error */

#endif /* AE_ERROR_FLAGS_H_ */
