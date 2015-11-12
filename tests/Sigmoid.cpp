#include "gtest/gtest.h"
#include "brainy/activation/sigmoid.hh"

TEST(SigmoidTest, Function)
{
  brainy::Sigmoid sigmoid;
  EXPECT_NEAR(0.50000, sigmoid.primary(0.00000), 0.00001);
  EXPECT_NEAR(0.62245, sigmoid.primary(0.50000), 0.00001);
  EXPECT_NEAR(0.73105, sigmoid.primary(1.00000), 0.00001);
};

TEST(Sigmoid, Derivative)
{
  brainy::Sigmoid sigmoid;
  EXPECT_NEAR(0.25000, sigmoid.derivative(0.50000), 0.00001);
  EXPECT_NEAR(0.23500, sigmoid.derivative(0.62245), 0.00001);
  EXPECT_NEAR(0.19661, sigmoid.derivative(0.73105), 0.00001);
};
