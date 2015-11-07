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

#ifndef BRAINY_NEURAL_TRAINER_TRAINER_HPP
#define BRAINY_NEURAL_TRAINER_TRAINER_HPP

#include <vector>
#include "brainy/neural/TrainingPair.hpp"
#include "brainy/neural/error/RMS.hpp"

namespace brainy {
  namespace neural {
    class Network;
    class TrainerPlugin;

    class Trainer {
    public:
      Trainer(Network& network) : network(network), error(*(new RMS())) {}
      void addPlugin(TrainerPlugin &plugin);

      virtual void preTrain();
      virtual void preEpoch();
      virtual void epoch() = 0;
      virtual void postEpoch();
      virtual void postTrain();

      virtual void train();

      virtual double getGoal() final;
      virtual void setGoal(const double goal) final;

      virtual void addTrainingPair(TrainingPair &pair);
      virtual void appendTrainingPairs(std::vector<TrainingPair*> &pairs);
      virtual double getPrevEpochError();
      virtual std::vector<TrainingPair*> &getTrainingSet();
      int getIteration();

    protected:
      Network& network;
      ErrorFunction& error;
      std::vector<TrainingPair*> trainingSet;
      std::vector<TrainerPlugin*> plugins;
      int maxEpochs = 100000000;
      int iteration;
      double goal = 0.1;
      double prevEpochError;
    };
  }
}

#endif
