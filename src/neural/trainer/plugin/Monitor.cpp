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

#include "brainy/neural/trainer/plugin/Monitor.hpp"
#include "brainy/neural/trainer/Trainer.hpp"
#include "brainy/Util.hpp"
#include <iostream>

namespace brainy {
  namespace neural {
    void Monitor::preTrain() {
      start = util::microtime();
    }

    void Monitor::postEpoch() {
      if (trainer->getIteration() % cycles == 1) {
        show();
      }
    }

    void Monitor::postTrain() {
      if (lastShow != trainer->getIteration() && trainer->getIteration() > 0) {
        show();
      }
    }

    void Monitor::show() {
      unsigned long long period = util::microtime() - start;

      std::cout << "------------------------------------" << std::endl;
      std::cout << "epoch           : " << trainer->getIteration() << std::endl;
      //          std::cout << "batch size      : " << trainer->getBatchSize() << std::endl;
      std::cout << "learning rate   : " << trainer->getLearningRate() << std::endl;
      // momentum
      // goal
      std::cout << "error           : " << trainer->getPrevEpochError() << std::endl;
      std::cout << "time            : " << (period / 1000.0 / 1000.0) << std::endl;
      std::cout << "speed           : " << trainer->getIteration() / (period / 1000.0 / 1000.0) << " epoch/s " << std::endl;
      std::cout << "epoch time      : " << (period / 1000.0 / 1000.0) / trainer->getIteration() << std::endl;

      lastShow = trainer->getIteration();
    }
  }
}
