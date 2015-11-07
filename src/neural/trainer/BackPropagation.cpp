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

#include "brainy/neural/trainer/BackPropagation.hpp"
#include "brainy/neural/network/FeedForward.hpp"
#include "brainy/neural/activation/ActivationFunction.hpp"
#include <iostream>
#include <cassert>

namespace brainy {
  namespace neural {
    void BackPropagation::preTrain() {
      for (auto layer : static_cast<FeedForward*>(&network)->getLayers()) {
        for (auto neuron : layer->getNeurons()) {
          auto data = new TrainingData();
          data->flatSpotFix = (neuron->hasActivation() && neuron->getActivation()->hasFlatSpot()) ? 0.1 : 0.0;
          neuron->setTrainingData(data);

          for (auto conn : neuron->getInputs()) {
            auto data = new ConnectionData();
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
      size_t size = batchSize;

      if (size == 0 || size > trainingSet.size()) {
        size = trainingSet.size();
      }

      for (TrainingPair *item : trainingSet) {
        network.setInput(item->input);
        network.activate();

        std::vector<double> patternError = error.calculate(network.getOutput(), item->output);
        propagate(patternError);

        batchIndex++;
        if (batchIndex % size == 0) {
          applyBatchChanges();
        }
      }
    }

    void BackPropagation::applyBatchChanges() {
      for (auto layer : static_cast<FeedForward*>(&network)->getLayers()) {
        for (auto neuron : layer->getNeurons()) {
          for (auto conn : neuron->getInputs()) {
            ConnectionData *cData = static_cast<ConnectionData*>(conn->getTrainingData());
            conn->setWeight(conn->getWeight() + cData->change);
            cData->change = 0.0;
          }
        }
      }
    }

    void BackPropagation::updateNeuronWeights(Neuron* neuron) {
      for (auto input : neuron->getInputs()) {
        TrainingData *data = static_cast<TrainingData*>(neuron->getTrainingData());

        double change = getLearningRate() * data->delta * input->getValue();
        change += getMomentum() * data->lastChange;

        data->lastChange = change;

        ConnectionData *cData = static_cast<ConnectionData*>(input->getTrainingData());
        cData->change += change;
      }
    }

    void BackPropagation::calculateOutputDeltas(std::vector<double> patternError) {
      auto layer = static_cast<FeedForward*>(&network)->getLayers().back();
      auto neurons = layer->getNeurons();

      assert(neurons.size() == patternError.size());

      for (size_t i = 0; i < neurons.size(); i++) {
        auto neuron = neurons.at(i);
        double derivative = neuron->getActivation()->derivative(neuron->getOutput());
        TrainingData *data = static_cast<TrainingData*>(neuron->getTrainingData());
        data->delta = patternError[i] * (derivative + data->flatSpotFix);

        updateNeuronWeights(neuron);
      }
    }

    void BackPropagation::calculateInternalDeltas() {
      auto layers = static_cast<FeedForward*>(&network)->getLayers();
      for (int i = layers.size() - 2; i >= 1; i--) {
        auto layer = layers.at(i);

        for (auto neuron : layer->getNeurons()) {
          if (neuron->isBias()) {
            continue;
          }

          double deltaSum = 0.0;
          for (auto conn : neuron->getOutputs()) {
            TrainingData *tData = static_cast<TrainingData*>(conn->getTarget().getTrainingData());
            deltaSum += conn->getWeight() * tData->delta;
          }

          TrainingData *data = static_cast<TrainingData*>(neuron->getTrainingData());
          double derivative = neuron->getActivation()->derivative(neuron->getOutput());
          data->delta = (derivative + data->flatSpotFix) * deltaSum;

          updateNeuronWeights(neuron);
        }
      }
    }

    void BackPropagation::propagate(std::vector<double> patternError) {
      calculateOutputDeltas(patternError);
      calculateInternalDeltas();
    }
  }
}
