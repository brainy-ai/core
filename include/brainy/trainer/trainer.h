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
#include "brainy/training_set.h"
#include "brainy/vector_training_set.h"
#include "brainy/error/rms.h"

namespace brainy {
  class Network;
  class TrainerPlugin;

  class Trainer {
  public:
    Trainer(Network& network, TrainingSet& set) : network(network), trainingSet(set), error(*(new RMS())) {}
    void addPlugin(TrainerPlugin &plugin);

    virtual void preTrain();
    virtual void preEpoch();
    virtual void epoch() = 0;
    virtual void postEpoch();
    virtual void postTrain();

    virtual void train();

    virtual double getGoal() final;
    virtual void setGoal(const double goal) final;

    virtual double getPrevEpochError();
    int getIteration();

    TrainingSet &getTrainingSet();

  protected:
    Network& network;
    TrainingSet &trainingSet;
    ErrorFunction& error;
    std::vector<TrainerPlugin*> plugins;
    int maxEpochs = 100000000;
    int iteration;
    double goal = 0.1;
    double prevEpochError;
  };
}

#endif
