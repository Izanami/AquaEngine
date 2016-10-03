#include "application.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {

static_assert(std::is_default_constructible<Application>::value);
static_assert(!std::is_move_constructible<Application>::value);
static_assert(!std::is_copy_constructible<Application>::value);

/// The fixture for testing class Application.
class ApplicationTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() { application = std::make_unique<Application>(); }

    /// Pointer to an instance class test
    std::unique_ptr<Application> application = nullptr;
};

TEST_F(ApplicationTest, Name) {
    application->SetName("Foo");
    ASSERT_STREQ(application->Name().c_str(), "Foo");
}

TEST_F(ApplicationTest, Version) {
    application->SetVersion(1, 1, 1);
    ASSERT_EQ(application->Version(), MakeVersion(1, 1, 1));
}

TEST_F(ApplicationTest, Informations) { application->Informations(); }
} /* ae::test */
