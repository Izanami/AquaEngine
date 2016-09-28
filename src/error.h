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

#ifndef AE_ERROR_H_
#define AE_ERROR_H_

#include "error/flags.h"

namespace ae {

/// \brief Handle errors
///
/// \sa ae::error::Flags
///
/// Example :
/// \code
///     class MyError : public ae::Error {
///         MyError(int code);
///         virtual MyError();
///     }
///
///     MyError::MyError(int code) {
///         if(code < 0)
///             flags_.set_error();
///     }
///
///     int main() {
///         MyError error(-1);
///
///         if (error.IsError) throw error.Message();
///     }
/// \endcode
class Error {
   public:
    Error();
    Error(const Error &) = delete;
    Error(Error &&) = delete;
    Error &operator=(const Error &) = delete;
    Error &operator=(Error &&) = delete;
    virtual ~Error();

    /// Returns the kSuccess bit flag.
    bool IsSuccess() const noexcept;

    /// Returns invert of the kSuccess bit flag.
    bool IsError() const noexcept;

    /// Returns the bits flags.
    error::Flags flags() const noexcept;

    /// \brief Analyse the errors for more details.
    ///
    /// \return The first element is for humans and the second is for the
    /// program.
    ///
    /// Example :
    ///
    /// \code
    ///     auto diagnostic = MyError(); // See ae::Error
    ///     if(diagnostic.second.is_error())
    ///     throw diagnostics.first
    /// \endcode
    virtual std::pair<std::string, error::Flags> DiagnosticAll() noexcept;

    /// \brief Human-readble message.
    ///
    /// Alias to DiagnosticAll().first
    /// \return String
    virtual std::string Message() noexcept;

   protected:
    /// \brief Flags state.
    /// \sa ae::error::Flags
    error::Flags flags_;
};
} /* ae */

#endif /* AE_ERROR_H_ */
