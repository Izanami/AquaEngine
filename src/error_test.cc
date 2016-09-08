#include "error.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<error::Vulkan>::value);
static_assert(!std::is_move_constructible<error::Vulkan>::value);
static_assert(!std::is_copy_constructible<error::Vulkan>::value);

class ErrorTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
};

TEST_F(ErrorTest, Vulkan) {
    ASSERT_STREQ(error::Vulkan::to_str(VK_SUCCESS),
                 "Vulkan : Command successfully completed");
}
