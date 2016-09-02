#include "glfw.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<GLFW>::value);
static_assert(!std::is_move_constructible<GLFW>::value);
static_assert(!std::is_copy_constructible<GLFW>::value);

class GLFWTest : public ::testing::Test {
   protected:
    virtual void SetUp() { window = std::make_unique<GLFW>(); }

    std::unique_ptr<GLFW> window = nullptr;
};

TEST_F(GLFWTest, PoolEvent) { ASSERT_TRUE(window->PoolEvent()); }
