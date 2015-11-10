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

#include "brainy/network/feed_forward.h"
#include "brainy/randomize/basic_randomize.h"

#include <stdexcept>
#include <iostream>
#include <cassert>

namespace brainy {
  void FeedForward::addLayer(Layer& layer) {
    layers.push_back(&layer);
  }

  void FeedForward::setInput(std::vector<double> input) {
    auto inputLayer = layers.front();
    auto neurons = inputLayer->getNeurons();
    auto neuronsCount = neurons.size() - (inputLayer->hasBias() ? 1 : 0);

    assert(neuronsCount == input.size());

    for (int i = 0; i < input.size(); i++) {
      neurons.at(i)->setInput(input.at(i));
    }
  }

  std::vector<double> FeedForward::getOutput() {
    auto neurons = layers.back()->getNeurons();
    std::vector<double> result;

    for (int i = 0; i < neurons.size(); i++) {
      result.push_back(neurons.at(i)->getOutput());
    }

    return result;
  }

  void FeedForward::activate() {
    for (auto it = layers.begin(); it != layers.end(); it++) {
      auto layer = *it;
      layer->activate();
    }
  }

  void FeedForward::finalize() {
    if (layers.size() < 2) {
      throw new std::logic_error("Network must have at least 2 layers.");
    }

    if (layers.back()->hasBias()) {
      throw new std::logic_error("Output layer cannot include bias.");
    }

    for (int i = 0; i < layers.size() - 1; i++) {
      Layer::interconnect(*layers.at(i), *layers.at(i+1));
    }

    getRandomizer().randomize(*this);
  }

  std::vector<Layer*> &FeedForward::getLayers() {
    return layers;
  }

  Randomize &FeedForward::getRandomizer() {
    auto *randomize = new BasicRandomize();
    return *randomize;
  }
}
