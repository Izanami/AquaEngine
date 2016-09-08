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
