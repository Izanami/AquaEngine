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

#include "flags.h"

namespace ae::error {
Flags::Flags() { SetSuccess(); }
Flags::~Flags() {}

Flags::Flags(const Flags &diagnostic) : std::bitset<CodeFlagsMax>(diagnostic) {}

Flags::Flags(Flags &&diagnostic)
    : std::bitset<CodeFlagsMax>(std::move(diagnostic)) {}

Flags &Flags::operator=(const Flags &diagnostic) {
    std::bitset<CodeFlagsMax>::operator=(diagnostic);
    return *this;
}

Flags &Flags::operator=(Flags &&diagnostic) {
    std::bitset<CodeFlagsMax>::operator=(std::move(diagnostic));
    return *this;
}

/* Success */
void Flags::SetSuccess() noexcept {
    set(static_cast<int>(CodeFlags::kSuccess));
}

void Flags::ResetSuccess() noexcept {
    reset(static_cast<int>(CodeFlags::kSuccess));
}

bool Flags::IsSuccess() const noexcept {
    return test(static_cast<int>(CodeFlags::kSuccess));
}

/* Error */
void Flags::SetError() noexcept { ResetSuccess(); }
void Flags::ResetError() noexcept { SetSuccess(); }
bool Flags::IsError() const noexcept { return !IsSuccess(); }

/* Verbose */
void Flags::SetVerbose() noexcept {
    set(static_cast<int>(CodeFlags::kVerbose));
}
void Flags::ResetVerbose() noexcept {
    reset(static_cast<int>(CodeFlags::kVerbose));
}
bool Flags::IsVerbose() const noexcept {
    return test(static_cast<int>(CodeFlags::kVerbose));
}

} /* ae::error */
