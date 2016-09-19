#include "error.h"

namespace ae {
Error::Error() {}
Error::~Error() {}

bool Error::IsSuccess() const noexcept { return flags_.IsSuccess(); }

bool Error::IsError() const noexcept { return flags_.IsError(); }

error::Flags Error::flags() const noexcept { return flags_; }

std::pair<std::string, error::Flags> Error::DiagnosticAll() noexcept {
    if (IsSuccess())
        return std::make_pair("Success", flags_);
    else
        return std::make_pair("Error", flags_);
}

std::string Error::Message() noexcept { return DiagnosticAll().first; }

} /* ae */
