#include "error.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {
static_assert(std::is_default_constructible<Error>::value);
static_assert(!std::is_move_constructible<Error>::value);
static_assert(!std::is_copy_constructible<Error>::value);

/// Fixture of ErrorTest.
class MyError : public ae::Error {
   public:
    //! \{
    MyError(int code) {
        if (code < 0) SetError();
    }
    ~MyError() {}
    //! \}
};

/// The fixture for testing class Error.
class ErrorTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() {
        error_success = std::make_unique<MyError>(1);
        error_error = std::make_unique<MyError>(-1);
    }

    /// Fixture when success.
    std::unique_ptr<MyError> error_success = nullptr;

    /// Fixture when failed.
    std::unique_ptr<MyError> error_error = nullptr;
};

TEST_F(ErrorTest, ToString) { ASSERT_EQ(error_success->ToString(), "Success"); }
} /* ae::test */
