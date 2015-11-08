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

#include "brainy/brainy.hpp"

int main(void) {
  brainy::VectorTrainingSet truth_table;
  truth_table.add({ 1,  1}, {-1});
  truth_table.add({-1, -1}, {-1});
  truth_table.add({ 1, -1}, { 1});
  truth_table.add({-1,  1}, { 1});

  brainy::Linear linear;
  brainy::Tanh activation;

  brainy::Layer inputLayer(2, &linear, true);
  brainy::Layer hiddenLayer(4, &activation, true);
  brainy::Layer outputLayer(1, &activation);

  brainy::FeedForward network;
  network.addLayer(inputLayer);
  network.addLayer(hiddenLayer);
  network.addLayer(outputLayer);
  network.finalize();

  brainy::BackPropagation trainer(network, truth_table);
  trainer.setLearningRate(0.5);
  trainer.setGoal(0.00001);
  trainer.setMomentum(0.1);
  brainy::Monitor monitor;
  trainer.addPlugin(monitor);
  brainy::SmartMomentum momentum;
  trainer.addPlugin(momentum);
  brainy::SmartLearningRate slr;
  trainer.addPlugin(slr);
  trainer.setBatchSize(0);
  trainer.train();

  // network.setInput({NN_TRUE, NN_FALSE});
  // network.activate();
  // brainy::util::print(network.getOutput());

  // network.setInput({NN_TRUE, NN_TRUE});
  // network.activate();
  // brainy::util::print(network.getOutput());

  return 0;
}
