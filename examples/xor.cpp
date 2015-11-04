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

#include "brainy/neural/Layer.hpp"
#include "brainy/neural/activation/Tanh.hpp"
#include "brainy/neural/activation/Sigmoid.hpp"
#include "brainy/neural/activation/Linear.hpp"
#include "brainy/neural/network/FeedForward.hpp"
#include "brainy/neural/trainer/BackPropagation.hpp"
#include "brainy/neural/trainer/plugin/SmartLearningRate.hpp"
#include "brainy/neural/trainer/plugin/SmartMomentum.hpp"
#include "brainy/neural/trainer/plugin/Monitor.hpp"
#include "brainy/neural/TrainingPair.hpp"
#include "brainy/neural/randomize/Basic.hpp"
#include "brainy/Util.hpp"

namespace neural = brainy::neural;
namespace util = brainy::util;

static std::vector<neural::TrainingPair*> truthTable = {
  new neural::TrainingPair({0.0, 0.0}, {0.0}),
  new neural::TrainingPair({0.0, 1.0}, {1.0}),
  new neural::TrainingPair({1.0, 0.0}, {1.0}),
  new neural::TrainingPair({1.0, 1.0}, {0.0})
};

int main(void) {
  neural::Linear linear;
  neural::Sigmoid sigmoid;

  neural::Layer inputLayer(2, &linear, true);
  neural::Layer hiddenLayer(2, &sigmoid, true);
  neural::Layer outputLayer(1, &sigmoid);

  neural::FeedForward network;
  network.addLayer(inputLayer);
  network.addLayer(hiddenLayer);
  network.addLayer(outputLayer);
  network.finalize();

  neural::BackPropagation trainer(network);
  trainer.appendTrainingPairs(truthTable);
  trainer.setLearningRate(0.5);
  trainer.setGoal(0.00000000001);
  trainer.setMomentum(0.1);
  neural::Monitor monitor;
  trainer.addPlugin(monitor);
  neural::SmartMomentum momentum;
  trainer.addPlugin(momentum);
  neural::SmartLearningRate slr;
  trainer.addPlugin(slr);
  trainer.setBatchSize(0);
  trainer.train();

  network.setInput({0.9, 0.0});
  network.activate();
  util::print(network.getOutput());

  network.setInput({0.9, 0.9});
  network.activate();
  util::print(network.getOutput());

  return 0;
}
