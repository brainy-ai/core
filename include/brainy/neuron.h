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

#ifndef BRAINY_NEURAL_NEURON_HPP
#define BRAINY_NEURAL_NEURON_HPP

#include <vector>
#include "brainy/connection.h"
#include "brainy/training_data.h"

namespace brainy {
  class ActivationFunction;

  class Neuron {
  public:
    Neuron(ActivationFunction *activation, bool bias);
    void activate();
    double getInput();
    void setInput(const double input);
    double getOutput();
    std::vector<Connection*>& getInputs();
    std::vector<Connection*>& getOutputs();
    bool isBias();
    TrainingData *getTrainingData();
    void setTrainingData(TrainingData *data);
    ActivationFunction *getActivation();
    bool hasActivation();
    const int id;

  private:
    bool bias;
    double inputsSum();
    ActivationFunction* activation;
    TrainingData *trainingData;
    std::vector<Connection*> inputs;
    std::vector<Connection*> outputs;
    double input = 0.0;
    double output = 0.0;
  };
}

#endif
