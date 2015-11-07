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
    void SmartLearningRate::init() {
      learningRate = dynamic_cast<LearningRate*>(getTrainer());
    }

    void SmartLearningRate::preTrain() {
      learningRate->setLearningRate(maxRate / getTrainer()->getTrainingSet().size());
    }

    void SmartLearningRate::postEpoch() {
      if (ready) {
        double ratio = getTrainer()->getPrevEpochError() / lastError;

        if (ratio > maxPerfInc) {
          adjustRate(rateDec);
        } else if (ratio < minPerfInc) {
          adjustRate(rateInc);
        }
      }
      else {
        ready = true;
      }
    }

    void SmartLearningRate::preEpoch() {
      lastError = getTrainer()->getPrevEpochError();
    }

    void SmartLearningRate::adjustRate(const double ratio) {
      double rate = learningRate->getLearningRate() * ratio;

      rate = fmin(rate, maxRate);
      rate = fmax(rate, minRate);

      learningRate->setLearningRate(rate);
    }
  }
}

