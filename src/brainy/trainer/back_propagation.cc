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

#include "brainy/trainer/back_propagation.hh"
#include "brainy/network/feed_forward.hh"
#include "brainy/activation/activation_function.hh"
#include <iostream>
#include <cassert>

namespace brainy {
  void BackPropagation::preTrain() {
    for (auto &layer : static_cast<FeedForward*>(&network)->getLayers()) {
      for (auto &neuron : layer->getNeurons()) {
        auto data = new BPTrainingData();
        data->flatSpotFix = (neuron->hasActivation() && neuron->getActivation()->hasFlatSpot()) ? 0.1 : 0.0;
        neuron->setTrainingData(data);

        for (auto &conn : neuron->getInputs()) {
          auto data = new BPConnectionData();
          conn->setTrainingData(data);
        }
      }
    }

    Trainer::preTrain();
  }

  void BackPropagation::setBatchSize(const int size) {
    // add some checks
    this->batchSize = size;
  }

  int BackPropagation::getBatchSize() {
    return batchSize;
  }

  void BackPropagation::epoch() {
    int batchIndex = 0;

    for (const TrainingPair &item : trainingSet) {
      network.setInput(item.input);
      network.activate();

      std::vector<double> patternError = error.calculate(network.getOutput(), item.output);
      propagate(patternError);

      batchIndex++;
      if (batchSize != 0 && batchIndex % batchSize == 0) {
        applyBatchChanges();
      }
    }

    if (batchSize == 0) {
      applyBatchChanges();
    }
  }

  void BackPropagation::applyBatchChanges() {
    for (auto &layer : static_cast<FeedForward*>(&network)->getLayers()) {
      for (auto &neuron : layer->getNeurons()) {
        for (auto &conn : neuron->getInputs()) {
          BPConnectionData *cData = static_cast<BPConnectionData*>(conn->getTrainingData());
          conn->setWeight(conn->getWeight() + cData->change);
          cData->change = 0.0;
        }
      }
    }
  }

  void BackPropagation::updateNeuronWeights(Neuron* const neuron) {
    for (auto &input : neuron->getInputs()) {
      BPTrainingData *data = static_cast<BPTrainingData*>(neuron->getTrainingData());

      double change = getLearningRate() * data->delta * input->getValue();
      change += getMomentum() * data->lastChange;

      data->lastChange = change;

      BPConnectionData *cData = static_cast<BPConnectionData*>(input->getTrainingData());
      cData->change += change;
    }
  }

  void BackPropagation::calculateOutputDeltas(const std::vector<double> &patternError) {
    auto layer = static_cast<FeedForward*>(&network)->getLayers().back();
    auto neurons = layer->getNeurons();

    assert(neurons.size() == patternError.size());

    for (size_t i = 0; i < neurons.size(); i++) {
      auto &neuron = neurons.at(i);
      double derivative = neuron->getActivation()->derivative(neuron->getOutput());
      BPTrainingData *data = static_cast<BPTrainingData*>(neuron->getTrainingData());
      data->delta = patternError[i] * (derivative + data->flatSpotFix);

      updateNeuronWeights(neuron);
    }
  }

  void BackPropagation::calculateInternalDeltas() {
    auto layers = static_cast<FeedForward*>(&network)->getLayers();
    for (size_t i = layers.size() - 2; i >= 1; i--) {
      auto layer = layers.at(i);

      for (auto &neuron : layer->getNeurons()) {
        if (neuron->isBias()) {
          continue;
        }

        double deltaSum = 0.0;
        for (auto &conn : neuron->getOutputs()) {
          BPTrainingData *tData = static_cast<BPTrainingData*>(conn->getTarget().getTrainingData());
          deltaSum += conn->getWeight() * tData->delta;
        }

        BPTrainingData *data = static_cast<BPTrainingData*>(neuron->getTrainingData());
        double derivative = neuron->getActivation()->derivative(neuron->getOutput());
        data->delta = (derivative + data->flatSpotFix) * deltaSum;

        updateNeuronWeights(neuron);
      }
    }
  }

  void BackPropagation::propagate(const std::vector<double> &patternError) {
    calculateOutputDeltas(patternError);
    calculateInternalDeltas();
  }
}
