#include "instance.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<Instance>::value);
static_assert(!std::is_move_constructible<Instance>::value);
static_assert(!std::is_copy_constructible<Instance>::value);

class InstanceTest : public ::testing::Test {
   protected:
    virtual void SetUp() { instance = std::make_unique<Instance>(); }

    std::unique_ptr<Instance> instance = nullptr;
};

TEST_F(InstanceTest, Create) { instance->Create(); }

TEST_F(InstanceTest, Extensions) {
    std::vector<const char*> extensions = {"Foo", "Baz"};
    instance->AddExtensions(extensions);
    ASSERT_EQ(instance->Extensions(), extensions);
}

TEST_F(InstanceTest, AvailableExtensions) {
    ASSERT_GT(instance->AvailableExtensions().size(), 0);
}

TEST_F(InstanceTest, MissingExtensions) {
    ASSERT_EQ(instance->MissingExtensions().size(), 0);

    std::vector<const char*> extensions = {"Foo", "Baz"};
    instance->AddExtensions(extensions);

    ASSERT_EQ(instance->MissingExtensions().size(), 2);
}

TEST_F(InstanceTest, AvailableValidation) {
    ASSERT_GT(instance->AvailableValidations().size(), 0);
}
