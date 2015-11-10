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

#include "brainy/layer.h"
#include "brainy/activation/linear.h"

#include <cstddef>

namespace brainy {
  Layer::Layer(unsigned int neurons) {
    init(neurons, nullptr, false);
  }

  Layer::Layer(unsigned int neurons, ActivationFunction* activation) {
    init(neurons, activation, false);
  }

  Layer::Layer(unsigned int neurons, ActivationFunction* activation, bool bias) {
    init(neurons, activation, bias);
  }

  Neuron& Layer::neuron(int index) {
    return *neurons.at(index);
  }

  std::vector<Neuron*>& Layer::getNeurons() {
    return neurons;
  }

  void Layer::activate() {
    for (auto it = neurons.begin(); it != neurons.end(); it++) {
      auto neuron = *it;
      neuron->activate();
    }
  }

  void Layer::init(unsigned int neurons, ActivationFunction* activation, bool bias) {
    for (int i = 0; i < neurons; i++) {
      Neuron *neuron = new Neuron(activation, false);
      this->neurons.push_back(neuron);
    }

    if (bias) {
      Neuron *biasNeuron = new Neuron(new Linear(), true);
      this->neurons.push_back(biasNeuron);
    }

    this->activation = activation;
  }

  bool Layer::hasBias() {
    for (auto it = neurons.begin(); it != neurons.end(); it++) {
      auto neuron = *it;
      if (neuron->isBias()) {
        return true;
      }
    }

    return false;
  }

  ActivationFunction *Layer::getActivation() {
    return activation;
  }

  void Layer::interconnect(Layer& source, Layer& target) {
    for (auto sit = source.getNeurons().begin(); sit != source.getNeurons().end(); sit++) {
      for (auto tit = target.getNeurons().begin(); tit != target.getNeurons().end(); tit++) {
        auto source = *sit;
        auto target = *tit;

        if (target->isBias()) {
          continue;
        }

        new Connection(*source, *target);
      }
    }
  }
}
