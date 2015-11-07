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

#ifndef BRAINY_NEURAL_TRAINER_PLUGIN_SMARTLEARNINGRATE_HPP
#define BRAINY_NEURAL_TRAINER_PLUGIN_SMARTLEARNINGRATE_HPP

#include "brainy/neural/trainer/plugin/TrainerPlugin.hpp"
#include "brainy/neural/trainer/LearningRate.hpp"

namespace brainy {
  namespace neural {
    class SmartLearningRate : public TrainerPlugin {
    public:
      void init();
      void preTrain();
      void preEpoch();
      void postEpoch();

    private:
      LearningRate *learningRate;
      void adjustRate(const double ratio);

      double minRate = 0.001;
      double maxRate = 0.900;
      double rateInc = 1.050;
      double rateDec = 0.700;
      double maxPerfInc = 1.04;
      double minPerfInc = 1.00;
      double lastError;
      bool ready = false;
    };
  }
}

#endif
