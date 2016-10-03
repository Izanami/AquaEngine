#include "result.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {
static_assert(std::is_default_constructible<Result>::value);
static_assert(!std::is_move_constructible<Result>::value);
static_assert(!std::is_copy_constructible<Result>::value);

/// Fixture of ResultTest.
class MyResult : public ae::Result {
   public:
    //! \{
    MyResult(int code) {
        if (code < 0) SetError();
    }
    ~MyResult() {}
    //! \}
};

/// The fixture for testing class Result.
class ResultTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() {
        result_success = std::make_unique<MyResult>(1);
        result_result = std::make_unique<MyResult>(-1);
    }

    /// Fixture when success.
    std::unique_ptr<MyResult> result_success = nullptr;

    /// Fixture when failed.
    std::unique_ptr<MyResult> result_result = nullptr;
};

TEST_F(ResultTest, ToString) {
    ASSERT_EQ(result_success->ToString(), "Success");
}
} /* ae::test */
