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
#include <stdexcept>

namespace brainy {
  void BackPropagation::preTrain() {
    auto layers = static_cast<FeedForward*>(&network)->getLayers();

    deltas.resize(layers.size());
    lastChanges.resize(layers.size());
    changes.resize(layers.size());

    // changes [ layer ] [ neuron ] [ input ]
    for (size_t i = 0; i < layers.size(); i++) {
      deltas[i].resize(layers[i]->getOutput().size(), 0.0);
      lastChanges[i].resize(layers[i]->getOutput().size(), 0.0);

      changes[i].resize(layers[i]->getNeurons());

      for (size_t n = 0; n < layers[i]->getNeurons(); n++) {
        changes[i][n].resize(layers[i]->inputsPerNeuron(), 0.0);
      }
    }

    // for (auto &layer : static_cast<FeedForward*>(&network)->getLayers()) {
    //   for (auto &neuron : layer->getNeurons()) {
    //     auto data = new BPTrainingData();
    //     data->flatSpotFix = neuron->getActivation().getFlatSpotFix();
    //     neuron->setTrainingData(data);

    //     for (auto &conn : neuron->getInputs()) {
    //       auto data = new BPConnectionData();
    //       conn->setTrainingData(data);
    //     }
    //   }
    // }

    Trainer::preTrain();
  }

  void BackPropagation::setBatchSize(const int size) {
    if (size < 0) {
      throw std::invalid_argument("batch size cannot be negative.");
    }
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

      auto layers = static_cast<FeedForward*>(&network)->getLayers();
      for (auto layer : layers) {
        layer->derivative();
      }

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
    auto layers = static_cast<FeedForward*>(&network)->getLayers();
    for (size_t l = 1; l < layers.size(); l++) {
      for (size_t n = 0; n < layers[l]->getNeurons(); n++) {
        for (size_t i = 0; i < layers[l]->inputsPerNeuron(); i++) {
          layers[l]->setWeight(n, i, changes[l][n][i]);
          changes[l][n][i] = 0.0;
        }
      }
    }
    // for (auto &layer : static_cast<FeedForward*>(&network)->getLayers()) {
    //   for (auto &neuron : layer->getNeurons()) {
    //     for (auto &conn : neuron->getInputs()) {
    //       BPConnectionData *cData = static_cast<BPConnectionData*>(conn->getTrainingData());
    //       conn->setWeight(conn->getWeight() + cData->change);
    //       cData->change = 0.0;
    //     }
    //   }
    // }
  }

  void BackPropagation::updateNeuronWeights(size_t const layerIndex, size_t const neuronIndex) {
    auto layers = static_cast<FeedForward*>(&network)->getLayers();

    assert(layerIndex > 0);
    for (size_t i = 0; i < layers[layerIndex]->inputsPerNeuron(); i++) {
      double change = getLearningRate() * deltas[layerIndex][neuronIndex] * layers[layerIndex-1]->getInput(); // input!
      change += getMomentum() * lastChanges[layerIndex][neuronIndex];
      lastChanges[layerIndex][neuronIndex] = change;

      changes[layerIndex][neuronIndex][i] += change;
    }
  }

  void BackPropagation::calculateOutputDeltas(const std::vector<double> &patternError) {
    std::vector<double> output = network.getOutput();
    size_t layerIndex = static_cast<FeedForward*>(&network)->getLayers().size() - 1;
    std::vector<double> derivatives = static_cast<FeedForward*>(&network)->getLayers().back()->getDerivatives();

    for (size_t i = 0; i < output.size(); i++) {
      deltas[layerIndex][i] = patternError[i] * (derivatives[i] + 0.1); // flat spot
      updateNeuronWeights(layerIndex, i);
    }
  }

  void BackPropagation::calculateInternalDeltas() {
    auto layers = static_cast<FeedForward*>(&network)->getLayers();
    for (size_t l = layers.size() - 2; l >= 1; l--) {
      auto layer = layers.at(l);
      auto nLayer = layers.at(l+1);

      for (size_t n = 0; n < layer->getNeurons(); n++) {
        double deltaSum = 0.0;

        for (size_t nn = 0; nn < nLayer->getNeurons(); nn++) {
          deltaSum += nLayer->getWeight(nn, n) * deltas[l+1][nn];
        }

        deltas[l][n] = (layer->getDerivatives()[n] + 0.1) * deltaSum;

        updateNeuronWeights(l, n);
      }
    }
    //     for (auto &conn : neuron->getOutputs()) {
    //       BPTrainingData *tData = static_cast<BPTrainingData*>(conn->getTarget().getTrainingData());
    //       deltaSum += conn->getWeight() * tData->delta;
    //     }

    //     BPTrainingData *data = static_cast<BPTrainingData*>(neuron->getTrainingData());
    //     double derivative = neuron->getActivation().derivative(neuron->getOutput());
    //     data->delta = (derivative + data->flatSpotFix) * deltaSum;

    //     updateNeuronWeights(neuron);
    //   }
    // }
  }

  void BackPropagation::propagate(const std::vector<double> &patternError) {
    calculateOutputDeltas(patternError);
    calculateInternalDeltas();
  }
}
