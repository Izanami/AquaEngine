#include "error.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<Error>::value);
static_assert(!std::is_move_constructible<Error>::value);
static_assert(!std::is_copy_constructible<Error>::value);

/// Fixture of ErrorTest.
class MyError : public ae::Error {
   public:
    //! \{
    MyError(int code) {
        if (code < 0) flags_.SetError();
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

TEST_F(ErrorTest, State) {
    ASSERT_EQ(error_success->IsSuccess(), true);
    ASSERT_EQ(error_error->IsError(), true);
}

TEST_F(ErrorTest, DiagnosticAll) {
    ASSERT_EQ(error_success->DiagnosticAll().second.IsSuccess(), true);
}

TEST_F(ErrorTest, Message) { ASSERT_EQ(error_success->Message(), "Success"); }
