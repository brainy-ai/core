#include "gtest/gtest.h"
#include "brainy/neuron.hh"
#include "brainy/activation/linear.hh"
#include "brainy/connection.hh"

#include <iostream>

static brainy::Linear linear;

TEST(NeuronTest, ActivationFunction) {
  brainy::Neuron neuron(linear, false);
  ASSERT_EQ(&linear, &neuron.getActivation());
}

TEST(NeuronTest, NotBias) {
  brainy::Neuron neuron(linear, false);
  ASSERT_EQ(false, neuron.isBias());
}

TEST(NeuronTest, Bias) {
  brainy::Neuron neuron(linear, true);
  ASSERT_EQ(true, neuron.isBias());
}

TEST(NeuronTest, InputNeuron) {
  brainy::Neuron neuron(linear, false);
  neuron.setInput(1.23);
  neuron.activate();
  ASSERT_NEAR(1.23, neuron.getOutput(), 0.001);
}

TEST(NeuronTest, BiasOutput) {
  brainy::Neuron neuron(linear, true);
  neuron.activate();
  ASSERT_NEAR(1.00, neuron.getOutput(), 0.001);
}
