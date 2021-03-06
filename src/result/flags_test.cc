#include "flags.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {
static_assert(std::is_default_constructible<result::Flags>::value);
static_assert(std::is_move_constructible<result::Flags>::value);
static_assert(std::is_copy_constructible<result::Flags>::value);

/// The fixture for testing class result::Flags.
class ErrorFlagsTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() { diagnostic = std::make_unique<result::Flags>(); }

    /// Pointer to an instance class test
    std::unique_ptr<result::Flags> diagnostic = nullptr;
};

TEST_F(ErrorFlagsTest, Success) {
    ASSERT_EQ(diagnostic->IsSuccess(), true);

    diagnostic->SetSuccess();
    ASSERT_EQ(diagnostic->IsSuccess(), true);

    diagnostic->ResetSuccess();
    ASSERT_EQ(diagnostic->IsSuccess(), false);
}

TEST_F(ErrorFlagsTest, Error) {
    ASSERT_EQ(diagnostic->IsError(), false);

    diagnostic->SetError();
    ASSERT_EQ(diagnostic->IsError(), true);

    diagnostic->ResetError();
    ASSERT_EQ(diagnostic->IsError(), false);
    ASSERT_EQ(diagnostic->IsSuccess(), true);
}
} /* ae::test */
