#include "flags.h"

namespace ae::error {
Flags::Flags() { set_success(); }
Flags::~Flags() {}

Flags::Flags(Flags &&diagnostic)
    : std::bitset<CodeFlagsMax>(std::move(diagnostic)) {}

Flags::Flags(const Flags &diagnostic) : std::bitset<CodeFlagsMax>(diagnostic) {}

Flags &Flags::operator=(const Flags &diagnostic) {
    std::bitset<CodeFlagsMax>::operator=(diagnostic);
    return *this;
}

Flags &Flags::operator=(Flags &&diagnostic) {
    std::bitset<CodeFlagsMax>::operator=(std::move(diagnostic));
    return *this;
}

/* Success */
void Flags::set_success() noexcept {
    set(static_cast<int>(CodeFlags::kSuccess));
}

void Flags::reset_success() noexcept {
    reset(static_cast<int>(CodeFlags::kSuccess));
}

bool Flags::is_success() const noexcept {
    return test(static_cast<int>(CodeFlags::kSuccess));
}

/* Error */
void Flags::set_error() noexcept { reset_success(); }
void Flags::reset_error() noexcept { set_success(); }
bool Flags::is_error() const noexcept { return !is_success(); }

/* Verbose */
void Flags::set_verbose() noexcept {
    set(static_cast<int>(CodeFlags::kVerbose));
}
void Flags::reset_verbose() noexcept {
    reset(static_cast<int>(CodeFlags::kVerbose));
}
bool Flags::is_verbose() const noexcept {
    return test(static_cast<int>(CodeFlags::kVerbose));
}

} /* ae::error */
