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

#include "brainy/layer.hh"
#include "brainy/activation/linear.hh"

#include <cstddef>

namespace brainy {
  Linear Layer::defaultActivation;
  Linear Layer::biasActivation;

  Layer::Layer(size_t const neurons) : activation(defaultActivation) {
    init(neurons, false);
  }

  Layer::Layer(size_t const neurons, ActivationFunction &activation) : activation(activation) {
    init(neurons, false);
  }

  Layer::Layer(size_t const neurons, ActivationFunction &activation, bool const bias) : activation(activation) {
    init(neurons, bias);
  }

  Neuron& Layer::neuron(size_t const index) const {
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

  void Layer::init(size_t const neurons, bool const bias) {
    for (size_t i = 0; i < neurons; i++) {
      Neuron *neuron = new Neuron(activation, false);
      this->neurons.push_back(neuron);
    }

    if (bias) {
      Neuron *biasNeuron = new Neuron(biasActivation, true);
      this->neurons.push_back(biasNeuron);
    }

    this->activation = activation;
  }

  bool Layer::hasBias() const {
    for (auto it = neurons.begin(); it != neurons.end(); it++) {
      auto neuron = *it;
      if (neuron->isBias()) {
        return true;
      }
    }

    return false;
  }

  ActivationFunction &Layer::getActivation() const {
    return activation;
  }

  void Layer::interconnect(Layer& source, Layer& target) {
    for (auto source : source.getNeurons()) {
      for (auto target : target.getNeurons()) {
        if (target->isBias()) {
          continue;
        }

        new Connection(*source, *target);
      }
    }
  }
}
