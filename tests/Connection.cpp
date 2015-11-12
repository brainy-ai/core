#include "gtest/gtest.h"
#include "brainy/neuron.hh"
#include "brainy/connection.hh"

TEST(ConnectionTest, Connections) {
  brainy::Neuron neuron1(nullptr, false);
  brainy::Neuron neuron2(nullptr, false);
  brainy::Connection connection(neuron1, neuron2);

  ASSERT_EQ(&neuron1, &connection.getSource());
  ASSERT_NE(&neuron2, &connection.getSource());

  ASSERT_EQ(&neuron2, &connection.getTarget());
  ASSERT_NE(&neuron1, &connection.getTarget());
}

TEST(ConnectionTest, ConnectionsInNeuron) {
  brainy::Neuron neuron1(nullptr, false);
  brainy::Neuron neuron2(nullptr, false);
  brainy::Connection connection(neuron1, neuron2);

  ASSERT_EQ(&connection, neuron1.getOutputs()[0]);
  ASSERT_EQ(&connection, neuron2.getInputs()[0]);
}
