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

#include "brainy/Layer.hpp"
#include "brainy/activation/Tanh.hpp"
#include "brainy/activation/Sigmoid.hpp"
#include "brainy/activation/Linear.hpp"
#include "brainy/network/FeedForward.hpp"
#include "brainy/trainer/BackPropagation.hpp"
#include "brainy/trainer/plugin/SmartLearningRate.hpp"
#include "brainy/trainer/plugin/SmartMomentum.hpp"
#include "brainy/trainer/plugin/Monitor.hpp"
#include "brainy/TrainingPair.hpp"
#include "brainy/randomize/BasicRandomize.hpp"
#include "brainy/Util.hpp"

const double NN_TRUE = 1.0;
const double NN_FALSE = -1.0;

static std::vector<brainy::TrainingPair*> truthTable = {
  new brainy::TrainingPair({NN_TRUE, NN_TRUE}, {NN_FALSE}),
  new brainy::TrainingPair({NN_FALSE, NN_TRUE}, {NN_TRUE}),
  new brainy::TrainingPair({NN_TRUE, NN_FALSE}, {NN_TRUE}),
  new brainy::TrainingPair({NN_TRUE, NN_TRUE}, {NN_FALSE})
};

int main(void) {
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

  brainy::BackPropagation trainer(network);
  trainer.appendTrainingPairs(truthTable);
  trainer.setLearningRate(0.5);
  trainer.setGoal(0.01);
  trainer.setMomentum(0.1);
  brainy::Monitor monitor;
  trainer.addPlugin(monitor);
  brainy::SmartMomentum momentum;
  trainer.addPlugin(momentum);
  brainy::SmartLearningRate slr;
  trainer.addPlugin(slr);
  trainer.setBatchSize(0);
  trainer.train();

  network.setInput({NN_TRUE, NN_FALSE});
  network.activate();
  util::print(network.getOutput());

  network.setInput({NN_TRUE, NN_TRUE});
  network.activate();
  util::print(network.getOutput());

  return 0;
}
