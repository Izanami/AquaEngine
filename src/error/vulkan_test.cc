#include "vulkan.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<error::Vulkan>::value);
static_assert(std::is_move_constructible<error::Vulkan>::value);
static_assert(std::is_copy_constructible<error::Vulkan>::value);

class ErrorVulkanTest : public ::testing::Test {
   protected:
    virtual void SetUp() { vulkan_error = std::make_unique<error::Vulkan>(); }

    std::unique_ptr<error::Vulkan> vulkan_error = nullptr;
};

TEST_F(ErrorVulkanTest, String) {
    ASSERT_STREQ(error::Vulkan::to_str(VK_SUCCESS),
                 "Vulkan : Command successfully completed");
}

TEST_F(ErrorVulkanTest, Result) {
    vulkan_error->set_result(VK_SUCCESS);
    ASSERT_EQ(vulkan_error->result(), VK_SUCCESS);
}

TEST_F(ErrorVulkanTest, Instance) {
    auto instance = std::make_shared<Instance>();
    vulkan_error->set_instance(instance);
    ASSERT_EQ(vulkan_error->instance(), instance);
}

TEST_F(ErrorVulkanTest, DiagnosticExtensions) {
    const std::vector<const char *> extensions = {"Buzz"};

    auto instance = std::make_shared<Instance>();
    vulkan_error->set_instance(instance);

    ASSERT_EQ(vulkan_error->DiagnosticExtensions().second.is_success(), true);

    instance->AddExtensions(extensions);

    ASSERT_EQ(vulkan_error->DiagnosticExtensions().first,
              "Vulkan : A requested extension is not supported : Buzz");

    ASSERT_EQ(vulkan_error->DiagnosticExtensions().second.is_error(), true);
}