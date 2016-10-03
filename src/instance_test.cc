#include "instance.h"
#include <gtest/gtest.h>
#include <memory>

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#define DISCARD
#endif
#endif

namespace ae::test {
static_assert(std::is_default_constructible<Instance>::value);
static_assert(std::is_move_constructible<Instance>::value);
static_assert(std::is_copy_constructible<Instance>::value);

/// The fixture for testing class Instance.
class InstanceTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() { instance = std::make_unique<Instance>(); }

    /// Pointer to an instance class test
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

TEST_F(InstanceTest, ExtensionsName) {
    ASSERT_EQ(instance->AvailableExtensionsName().size(),
              instance->AvailableExtensions().size());
}

TEST_F(InstanceTest, MissingExtensions) {
    ASSERT_EQ(instance->MissingExtensions().size(), 0);

    std::vector<const char*> extensions = {"Foo", "Baz"};
    instance->AddExtensions(extensions);

    ASSERT_EQ(instance->MissingExtensions().size(), 2);
}

TEST_F(InstanceTest, Validations) {
    std::vector<const char*> validations = {"Foo", "Baz"};
    instance->AddValidations(validations);
    ASSERT_EQ(instance->Validations(), validations);
    ASSERT_EQ(instance->Validations().size(), 2);
}

TEST_F(InstanceTest, AvailableValidation) {
#ifndef DISCARD
    ASSERT_GT(instance->AvailableValidations().size(), 0);
#else
    ASSERT_EQ(instance->AvailableValidations().size(), 0);
#endif
}

TEST_F(InstanceTest, ValidationsName) {
    ASSERT_EQ(instance->AvailableValidationsName().size(),
              instance->AvailableValidations().size());
}

TEST_F(InstanceTest, MissingValidations) {
    ASSERT_EQ(instance->MissingValidations().size(), 0);

    std::vector<const char*> validations = {"Foo", "Baz"};
    instance->AddValidations(validations);

    ASSERT_EQ(instance->MissingValidations().size(), 2);
}

TEST_F(InstanceTest, DefaultValidations) {
    instance->AddDefaultValidations();
    ASSERT_GT(instance->Validations().size(), 0);
}
} /* ae::test */
