#include "vulkan.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {
static_assert(std::is_default_constructible<result::Vulkan>::value);
static_assert(std::is_move_constructible<result::Vulkan>::value);
static_assert(std::is_copy_constructible<result::Vulkan>::value);

/// The fixture for testing class result::Vulkan.
class ErrorVulkanTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() { vulkan_result = std::make_unique<result::Vulkan>(); }

    /// Pointer to an instance class test
    std::unique_ptr<result::Vulkan> vulkan_result = nullptr;
};

TEST_F(ErrorVulkanTest, String) {
    ASSERT_STREQ(result::Vulkan::ToString(VK_SUCCESS),
                 "Vulkan : Command successfully completed");
}

TEST_F(ErrorVulkanTest, Result) {
    vulkan_result->SetResult(VK_SUCCESS);
    ASSERT_EQ(vulkan_result->Result(), VK_SUCCESS);
}

} /* ae::test */
