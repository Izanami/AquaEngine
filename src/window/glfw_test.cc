#ifdef GLFW_VERSION_3

#include "glfw.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {
static_assert(std::is_default_constructible<window::GLFW>::value);
static_assert(std::is_move_constructible<window::GLFW>::value);
static_assert(!std::is_copy_constructible<window::GLFW>::value);

class GLFWTest : public ::testing::Test {
   protected:
    virtual void SetUp() { window = std::make_unique<window::GLFW>(); }

    std::unique_ptr<window::GLFW> window = nullptr;
};

TEST_F(GLFWTest, Move) { ASSERT_TRUE(window->PoolEvent()); }

TEST_F(GLFWTest, PoolEvent) { ASSERT_TRUE(window->PoolEvent()); }

TEST_F(GLFWTest, Extensions) { ASSERT_GT(window->extensions().size(), 0); }
} /* ae::test */

#endif
