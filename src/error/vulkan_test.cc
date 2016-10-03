#include "vulkan.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {
static_assert(std::is_default_constructible<error::Vulkan>::value);
static_assert(std::is_move_constructible<error::Vulkan>::value);
static_assert(std::is_copy_constructible<error::Vulkan>::value);

/// The fixture for testing class error::Vulkan.
class ErrorVulkanTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() { vulkan_error = std::make_unique<error::Vulkan>(); }

    /// Pointer to an instance class test
    std::unique_ptr<error::Vulkan> vulkan_error = nullptr;
};

TEST_F(ErrorVulkanTest, String) {
    ASSERT_STREQ(error::Vulkan::ToString(VK_SUCCESS),
                 "Vulkan : Command successfully completed");
}

TEST_F(ErrorVulkanTest, Result) {
    vulkan_error->SetResult(VK_SUCCESS);
    ASSERT_EQ(vulkan_error->Result(), VK_SUCCESS);
}

} /* ae::test */
