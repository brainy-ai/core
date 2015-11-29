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
#include "brainy/brainy.hh"

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
  brainy::InputLayer inputLayer(2);
  // Hidden layer with 2 neurons, tanh activation and BIAS
  brainy::TanhLayer hiddenLayer(6);
  // Output layer with 1 neuron, tanh activation
  brainy::TanhLayer outputLayer(1);

  // Create network, and plug defined layers
  brainy::FeedForward network;
  network.addLayer(inputLayer);
  network.addLayer(hiddenLayer);
  network.addLayer(outputLayer);
  network.finalize();

  // for (int i = 0; i < 500000; i++) {
  //   network.activate();
  // }
  // return 0;

  brainy::BackPropagation trainer(network, truthTable);

  // Monitor plugin to see what's happening during training
  brainy::Monitor monitor;
  trainer.addPlugin(monitor);

  //brainy::SmartLearningRate slr;
  //  trainer.addPlugin(slr);

  // Set training parameters
  trainer.setGoal(0.01);
  trainer.setLearningRate(0.3);
  trainer.setMomentum(0.1);

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
