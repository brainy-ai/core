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

#ifndef BRAINY_NEURON_HH
#define BRAINY_NEURON_HH

#include <vector>
#include "brainy/connection.hh"
#include "brainy/training_data.hh"

namespace brainy {
  class ActivationFunction;

  class Neuron {
  public:
    Neuron(ActivationFunction* const activation, bool const bias);
    void activate();
    double getInput() const;
    void setInput(double const input);
    double getOutput() const;
    std::vector<Connection*>& getInputs();
    std::vector<Connection*>& getOutputs();
    bool isBias() const;
    TrainingData *getTrainingData() const;
    void setTrainingData(TrainingData *data);
    ActivationFunction *getActivation() const;
    bool hasActivation() const;
    int const id;

  private:
    bool const bias;
    double inputsSum() const;
    ActivationFunction *activation;
    TrainingData *trainingData;
    std::vector<Connection*> inputs;
    std::vector<Connection*> outputs;
    double input = 0.0;
    double output = 0.0;
  };
}

#endif
