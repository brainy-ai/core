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

#include "brainy/util.h"
#include "brainy/neuron.h"
#include "brainy/activation/activation_function.h"
#include <iostream>

namespace brainy {

Neuron::Neuron(ActivationFunction* activation, bool bias) : id(util::id()) {
  // @todo: dont allow to set empty activation
  this->activation = activation;

  this->bias = bias;

  if (bias) {
    input = 1.0;
  }
}

double Neuron::inputsSum() {
  double sum = 0.0;
  for (auto it = inputs.begin(); it != inputs.end(); it++) {
    auto conn = *it;
    sum += conn->getWeighedValue();
  }

  return sum;
}

bool Neuron::isBias() {
  return bias;
}

void Neuron::setInput(const double input) {
  this->input = input;
}

void Neuron::activate() {
  double value = inputs.empty() ? input : inputsSum();
  // output = (activation != nullptr) ? activation->primary(value) : value;
  output = activation->primary(value);
}

double Neuron::getOutput() {
  return output;
}

std::vector<Connection*>& Neuron::getInputs() {
  return inputs;
}

std::vector<Connection*>& Neuron::getOutputs() {
  return outputs;
}

void Neuron::setTrainingData(TrainingData *data) {
  this->trainingData = data;
}

TrainingData *Neuron::getTrainingData() {
  return trainingData;
}

ActivationFunction *Neuron::getActivation() {
  return activation;
}

bool Neuron::hasActivation() {
  return (activation != nullptr);
}

}
