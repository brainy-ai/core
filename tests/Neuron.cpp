#include "gtest/gtest.h"
#include "brainy/neuron.h"
#include "brainy/activation/sigmoid.h"
#include "brainy/connection.h"

#include <iostream>

TEST(NeuronTest, ActivationFunction) {
  brainy::Neuron neuron(nullptr, false);
  ASSERT_EQ(nullptr, neuron.getActivation());
}

TEST(NeuronTest, NotBias) {
  brainy::Neuron neuron(nullptr, false);
  ASSERT_EQ(false, neuron.isBias());
}

TEST(NeuronTest, Bias) {
  brainy::Neuron neuron(nullptr, true);
  ASSERT_EQ(true, neuron.isBias());
}

TEST(NeuronTest, InputNeuron) {
  brainy::Neuron neuron(nullptr, false);
  neuron.setInput(1.23);
  neuron.activate();
  ASSERT_NEAR(1.23, neuron.getOutput(), 0.001);
}

TEST(NeuronTest, BiasOutput) {
  brainy::Neuron neuron(nullptr, true);
  neuron.activate();
  ASSERT_NEAR(1.00, neuron.getOutput(), 0.001);
}
