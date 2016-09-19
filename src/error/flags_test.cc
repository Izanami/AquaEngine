#include "flags.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<error::Flags>::value);
static_assert(std::is_move_constructible<error::Flags>::value);
static_assert(std::is_copy_constructible<error::Flags>::value);

class ErrorFlagsTest : public ::testing::Test {
   protected:
    virtual void SetUp() { diagnostic = std::make_unique<error::Flags>(); }

    std::unique_ptr<error::Flags> diagnostic = nullptr;
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
