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

#include "error.h"

namespace ae {
Error::Error() {}
Error::~Error() {}

error::Flags Error::Details() const noexcept { return flags_; }

std::pair<std::string, error::Flags> Error::DiagnosticAll() noexcept {
    if (flags_.IsSuccess())
        return std::make_pair("Success", flags_);
    else
        return std::make_pair("Error", flags_);
}

std::string Error::Message() noexcept { return DiagnosticAll().first; }

} /* ae */
