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
    application->set_name("Foo");
    ASSERT_STREQ(application->name().c_str(), "Foo");
}

TEST_F(ApplicationTest, Version) {
    application->set_version(1, 1, 1);
    ASSERT_EQ(application->version(), MakeVersion(1, 1, 1));
}

TEST_F(ApplicationTest, Informations) { application->informations(); }
