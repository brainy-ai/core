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

#include "brainy/neural/trainer/plugin/SmartMomentum.hpp"

#include "brainy/neural/trainer/plugin/Plugin.hpp"
#include "brainy/neural/trainer/Trainer.hpp"
#include <cmath>
#include <iostream>

namespace brainy {
  namespace neural {
    static double MIN_IMPROVEMENT = 0.0001;

    void SmartMomentum::preTrain() {
      trainer->setMomentum(0.0);
      cycle = 0;
    }

    void SmartMomentum::preEpoch() {
      if (ready) {
        double currError = trainer->getPrevEpochError();
        double improvement = (currError - lastError) / lastError;

        if ((improvement > 0.0) || (fabs(improvement) < MIN_IMPROVEMENT)) {
          cycle++;

          if (cycle > 10) {
            cycle = 0;

            if (trainer->getMomentum() == 0.0) {
              trainer->setMomentum(0.1);
            }

            trainer->setMomentum(trainer->getMomentum() * (1.0 + 0.01));
            // std::cout << "momentum = " << trainer->getMomentum() << std::endl;
          }
        }
        else {
          trainer->setMomentum(0.0);
        }
      }
    }

    void SmartMomentum::postEpoch() {
      lastError = trainer->getPrevEpochError();
      ready = true;
    }
  }
}

