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

#include "result/flags.h"

namespace ae {

/// \brief Handle results
///
/// \sa ae::result::Flags
///
/// Example :
/// \code
///     class MyResult : public ae::Result {
///         MyResult(int code);
///         virtual MyResult();
///     }
///
///     MyResult::MyResult(int code) {
///         if(code < 0)
///             SetError();
///     }
///
///     int main() {
///         MyResult result(-1);
///
///         if (result.IsResult()) throw result.Message();
///     }
/// \endcode
class Result : public result::Flags {
   public:
    Result();
    Result(const Result &) = delete;
    Result(Result &&) = delete;
    Result &operator=(const Result &) = delete;
    Result &operator=(Result &&) = delete;
    virtual ~Result();

    /// \brief Human-readble message.
    ///
    /// \return String
    virtual std::string ToString() noexcept;
};
} /* ae */

#endif /* AE_ERROR_H_ */
