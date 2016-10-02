#include "window.h"
#include <gtest/gtest.h>
#include <memory>

namespace ae::test {
static_assert(std::is_default_constructible<Window>::value);
static_assert(!std::is_move_constructible<Window>::value);
static_assert(!std::is_copy_constructible<Window>::value);

/// The fixture for testing class Window.
class WindowTest : public ::testing::Test {
   protected:
    /// Set fixture
    virtual void SetUp() { window = std::make_unique<Window>(); }

    /// Pointer to an instance class test
    std::unique_ptr<Window> window = nullptr;
};

TEST_F(WindowTest, PoolEvent) { ASSERT_FALSE(window->PoolEvent()); }
TEST_F(WindowTest, Create) { Window::Create(); }
} /* ae::test */
