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

#include "brainy/trainer/plugin/monitor.h"
#include "brainy/trainer/trainer.h"
#include "brainy/util.h"
#include <iostream>

namespace brainy {
  void Monitor::init() {
    learningRate = dynamic_cast<LearningRate*>(getTrainer());
    momentum = dynamic_cast<Momentum*>(getTrainer());
  }

  void Monitor::preTrain() {
    start = util::microtime();
  }

  void Monitor::postEpoch() {
    if (getTrainer()->getIteration() % cycles == 0) {
      show();
    }
  }

  void Monitor::postTrain() {
    if (lastShow != getTrainer()->getIteration() && getTrainer()->getIteration() > 0) {
      show();
    }
  }

  void Monitor::show() {
    unsigned long long period = util::microtime() - start;

    std::cout << "------------------------------------" << std::endl;
    std::cout << "epoch           : " << getTrainer()->getIteration() << std::endl;
    if (learningRate) {
      std::cout << "learning rate   : " << learningRate->getLearningRate() << std::endl;
    }
    if (momentum) {
      std::cout << "momentum        : " << momentum->getMomentum() << std::endl;
    }
    std::cout << "error           : " << getTrainer()->getPrevEpochError() << std::endl;
    std::cout << "time            : " << (period / 1000.0 / 1000.0) << "s" << std::endl;
    std::cout << "speed           : " << getTrainer()->getIteration() / (period / 1000.0 / 1000.0) << " epoch/s " << std::endl;
    std::cout << "epoch time      : " << (period / 1000.0 / 1000.0) / getTrainer()->getIteration() << std::endl;

    lastShow = getTrainer()->getIteration();
  }
}
