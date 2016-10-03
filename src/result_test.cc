#include "result.h"
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
        result_success = std::make_unique<MyError>(1);
        result_result = std::make_unique<MyError>(-1);
    }

    /// Fixture when success.
    std::unique_ptr<MyError> result_success = nullptr;

    /// Fixture when failed.
    std::unique_ptr<MyError> result_result = nullptr;
};

TEST_F(ErrorTest, ToString) { ASSERT_EQ(result_success->ToString(), "Success"); }
} /* ae::test */
