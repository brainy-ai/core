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

#include "brainy/trainer/plugin/smart_momentum.hh"

#include "brainy/trainer/trainer.hh"
#include "brainy/trainer/momentum.hh"
#include <cmath>
#include <stdexcept>

namespace brainy {
  static double MIN_IMPROVEMENT = 0.0001;

  void SmartMomentum::init() {
    momentum = dynamic_cast<Momentum*>(getTrainer());
    if (!momentum) {
      throw new std::invalid_argument("SmartMomentum can be used only with trainers implementing Momentum interface.");
    }
  }

  void SmartMomentum::preTrain() {
    momentum->setMomentum(0.0);
    cycle = 0;
  }

  void SmartMomentum::postEpoch() {
    if (ready) {
      double currError = getTrainer()->getEpochError();
      double improvement = (currError - lastError) / lastError;

      if ((improvement > 0.0) || (fabs(improvement) < MIN_IMPROVEMENT)) {
        cycle++;

        if (cycle > 10) {
          cycle = 0;

          if (momentum->getMomentum() == 0.0) {
            momentum->setMomentum(0.1);
          }

          momentum->setMomentum(momentum->getMomentum() * (1.0 + 0.01));
        }
      }
      else {
        momentum->setMomentum(0.0);
      }
    } else {
      ready = true;
    }
  }

  void SmartMomentum::preEpoch() {
    lastError = getTrainer()->getEpochError();
  }
}
