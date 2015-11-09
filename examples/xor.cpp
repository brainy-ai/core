/*
 *
 * Copyright 2015 Krzysztof Magosa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <iomanip>
#include "brainy/brainy.hpp"

int main(void) {
  // XOR truth table
  // -1 for false, 1 for true
  brainy::VectorTrainingSet truthTable;
  truthTable.add({ 1,  1}, {-1});
  truthTable.add({-1, -1}, {-1});
  truthTable.add({ 1, -1}, { 1});
  truthTable.add({-1,  1}, { 1});

  // Activation functions
  brainy::Linear linear;
  brainy::Tanh activation;

  // Input layer with 2 neurons, linear activation and BIAS
  brainy::Layer inputLayer(2, &linear, true);
  // Hidden layer with 4 neurons, tanh activation and BIAS
  brainy::Layer hiddenLayer(4, &activation, true);
  // Output layer with 1 neuron, tanh activation
  brainy::Layer outputLayer(1, &activation);

  // Create network, and plug defined layers
  brainy::FeedForward network;
  network.addLayer(inputLayer);
  network.addLayer(hiddenLayer);
  network.addLayer(outputLayer);
  network.finalize();

  brainy::BackPropagation trainer(network, truthTable);

  // Monitor plugin to see what's happening during training
  brainy::Monitor monitor;
  trainer.addPlugin(monitor);

  // Smart momentum for better training
  brainy::SmartMomentum momentum;
  trainer.addPlugin(momentum);

  // Smart learning rate for better training
  brainy::SmartLearningRate slr;
  trainer.addPlugin(slr);

  // This is our desirable error
  trainer.setGoal(0.01);

  // Use batch mode with batch size equal to training set
  trainer.setBatchSize(0);

  // Do training
  trainer.train();

  // Show the results of training
  std::cout
    << "\nResult\n======\n"
    << std::fixed;
  for (auto &item : truthTable) {
    network.setInput(item.input);
    network.activate();

    std::cout
      << std::setprecision(0)
      << std::setw(3)
      << item.input[0]
      << ", "
      << std::setw(3)
      << item.input[1]
      << " -> "
      << std::setprecision(3)
      << std::setw(6)
      << network.getOutput()[0]
      << " (expected: "
      << std::setw(6)
      << item.output[0]
      << ")"
      << std::endl;
  }

  return 0;
}
