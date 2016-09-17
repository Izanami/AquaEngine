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
    ASSERT_EQ(diagnostic->is_success(), true);

    diagnostic->set_success();
    ASSERT_EQ(diagnostic->is_success(), true);

    diagnostic->reset_success();
    ASSERT_EQ(diagnostic->is_success(), false);
}

TEST_F(ErrorFlagsTest, Error) {
    ASSERT_EQ(diagnostic->is_error(), false);

    diagnostic->set_error();
    ASSERT_EQ(diagnostic->is_error(), true);

    diagnostic->reset_error();
    ASSERT_EQ(diagnostic->is_error(), false);
    ASSERT_EQ(diagnostic->is_success(), true);
}
