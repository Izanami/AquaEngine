#include "window.h"
#include <gtest/gtest.h>
#include <memory>

using namespace ae;

static_assert(std::is_default_constructible<Window>::value);
static_assert(!std::is_move_constructible<Window>::value);
static_assert(!std::is_copy_constructible<Window>::value);

class WindowTest : public ::testing::Test {
   protected:
    virtual void SetUp() { window = std::make_unique<Window>(); }

    std::unique_ptr<Window> window = nullptr;
};

TEST_F(WindowTest, PoolEvent) { ASSERT_FALSE(window->PoolEvent()); }
