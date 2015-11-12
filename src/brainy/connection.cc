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

#include "brainy/connection.hh"
#include <iostream>
#include <cassert>
#include "brainy/neuron.hh"
#include "brainy/util.hh"

namespace brainy {
  Connection::Connection(Neuron& source, Neuron& target) : id(util::id()),
                                                           source(&source),
                                                           target(&target) {
    assert(target.isBias() == false);

    source.getOutputs().push_back(this);
    target.getInputs().push_back(this);
  }

  Neuron& Connection::getSource() const {
    return *source;
  }

  Neuron& Connection::getTarget() const {
    return *target;
  }

  double Connection::getWeight() const {
    return weight;
  }

  void Connection::setWeight(double const weight) {
    this->weight = weight;
  }

  double Connection::getValue() const {
    return source->getOutput();
  }

  double Connection::getWeighedValue() const {
    return getValue() * weight;
  }

  void Connection::setTrainingData(TrainingData* const data) {
    trainingData = data;
  }

  TrainingData *Connection::getTrainingData() const {
    return trainingData;
  }
}
