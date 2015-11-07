#include "gtest/gtest.h"
#include "brainy/activation/Tanh.hpp"

TEST(Tanh, Function)
{
  brainy::Tanh tanh;
  EXPECT_NEAR(-0.76159, tanh.primary(-1.00000), 0.00001);
  EXPECT_NEAR( 0.00000, tanh.primary( 0.00000), 0.00001);
  EXPECT_NEAR( 0.76159, tanh.primary( 1.00000), 0.00001);
};

TEST(Tanh, Derivative)
{
  brainy::Tanh tanh;
  EXPECT_NEAR(0.41998, tanh.derivative(-0.76159), 0.00001);
  EXPECT_NEAR(1.00000, tanh.derivative( 0.00000), 0.00001);
  EXPECT_NEAR(0.41998, tanh.derivative( 0.76159), 0.00001);
};
