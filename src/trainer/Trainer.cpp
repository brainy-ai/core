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

#include "brainy/trainer/Trainer.hpp"
#include "brainy/trainer/plugin/TrainerPlugin.hpp"
#include "brainy/network/Network.hpp"

#include <iostream>

namespace brainy {
  void Trainer::preTrain() {
    iteration = 0;

    for (auto plugin : plugins) {
      plugin->preTrain();
    }
  }

  void Trainer::preEpoch() {
    iteration++;
    prevEpochError = error.getResult();
    error.reset();

    for (auto plugin : plugins) {
      plugin->preEpoch();
    }
  }

  void Trainer::postEpoch() {
    for (auto plugin : plugins) {
      plugin->postEpoch();
    }
  }

  void Trainer::postTrain() {
    for (auto plugin : plugins) {
      plugin->postTrain();
    }
  }

  void Trainer::train() {
    preTrain();

    while (true) {
      preEpoch();
      epoch();
      postEpoch();

      if (prevEpochError <= goal || iteration >= maxEpochs) {
        break;
      }
    }

    postTrain();
  }

  double Trainer::getGoal() {
    return goal;
  }

  void Trainer::setGoal(const double goal) {
    this->goal = goal;
  }

  double Trainer::getPrevEpochError() {
    return prevEpochError;
  }

  void Trainer::addPlugin(TrainerPlugin &plugin) {
    plugins.push_back(&plugin);
    plugin.setTrainer(*this);
    plugin.init();
  }

  int Trainer::getIteration() {
    return iteration;
  }

  TrainingSet &Trainer::getTrainingSet() {
    return trainingSet;
  }
}
