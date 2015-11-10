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

#include "brainy/connection.h"
#include "brainy/neuron.h"
#include "brainy/util.h"

#include <iostream>
#include <cassert>

namespace brainy {
  Connection::Connection(Neuron& source, Neuron& target) : id(util::id()) {
    assert(target.isBias() == false);

    this->source = &source;
    this->target = &target;

    source.getOutputs().push_back(this);
    target.getInputs().push_back(this);
  }

  Neuron& Connection::getSource() {
    return *source;
  }

  Neuron& Connection::getTarget() {
    return *target;
  }

  double Connection::getWeight() {
    return this->weight;
  }

  void Connection::setWeight(const double weight) {
    this->weight = weight;
  }

  double Connection::getValue() {
    return source->getOutput();
  }

  double Connection::getWeighedValue() {
    return getValue() * weight;
  }

  void Connection::setTrainingData(TrainingData *data) {
    this->trainingData = data;
  }

  TrainingData *Connection::getTrainingData() {
    return trainingData;
  }
}
