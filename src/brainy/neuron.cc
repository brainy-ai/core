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

#include "brainy/neuron.hh"
#include <iostream>
#include "brainy/util.hh"
#include "brainy/activation/activation_function.hh"

namespace brainy {
  Neuron::Neuron(ActivationFunction &activation, bool const bias) : id(util::id()),
                                                                    bias(bias),
                                                                    activation(activation) {
    if (bias) {
      input = 1.0;
    }
  }

  double Neuron::inputsSum() const {
    double sum = 0.0;
    for (auto conn : inputs) {
      sum += conn->getWeighedValue();
    }

    return sum;
  }

  void Neuron::activate() {
    double value = inputs.empty() ? input : inputsSum();
    // output = (activation != nullptr) ? activation->primary(value) : value;
    output = activation.primary(value);
  }

  void Neuron::setTrainingData(TrainingData *data) {
    this->trainingData = data;
  }

  ActivationFunction &Neuron::getActivation() const {
    return activation;
  }
}
