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

#include "brainy/neural/trainer/Trainer.hpp"
#include "brainy/neural/trainer/plugin/SmartLearningRate.hpp"
#include <cmath>

#include <iostream>

namespace brainy {
  namespace neural {
    void SmartLearningRate::preTrain() {
      trainer->setLearningRate(maxRate / trainer->getTrainingSet().size());
    }

    void SmartLearningRate::preEpoch() {
      if (ready) {
        double ratio = trainer->getPrevEpochError() / lastError;

        if (ratio > maxPerfInc) {
          adjustRate(rateDec);
        } else if (ratio < minPerfInc) {
          adjustRate(rateInc);
        }
      }
    }

    void SmartLearningRate::postEpoch() {
      lastError = trainer->getPrevEpochError();
      ready = true;
    }

    void SmartLearningRate::adjustRate(const double ratio) {
      double rate = trainer->getLearningRate() * ratio;

      rate = fmin(rate, maxRate);
      rate = fmax(rate, minRate);

      trainer->setLearningRate(rate);
    }
  }
}

