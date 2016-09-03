#include "application.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<Application>::value);
static_assert(!std::is_move_constructible<Application>::value);
static_assert(!std::is_copy_constructible<Application>::value);

class ApplicationTest : public ::testing::Test {
   protected:
    virtual void SetUp() { application = std::make_unique<Application>(); }

    std::unique_ptr<Application> application = nullptr;
};

TEST_F(ApplicationTest, Name) {
    application->Name("Foo");
    ASSERT_STREQ(application->Name().c_str(), "Foo");
}

TEST_F(ApplicationTest, Version) {
    application->Version(1, 1, 1);
    ASSERT_EQ(application->Version(), MakeVersion(1, 1, 1));
}
