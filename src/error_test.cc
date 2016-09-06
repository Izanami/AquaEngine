#include "error.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

class ErrorTest : public ::testing::Test {
   protected:
    virtual void SetUp() {}
};

TEST_F(ErrorTest, Vulkan) {
    ASSERT_STREQ(ae::error::Vulkan::to_str(VK_SUCCESS),
                 "Vulkan : Command successfully completed");
}
