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

#ifndef BRAINY_CONNECTION_HH
#define BRAINY_CONNECTION_HH

namespace brainy {
  class Neuron;
  class TrainingData;

  /**
   * This class represents connection between two neurons.
   */
  class Connection {
  public:
    Connection(Neuron& source, Neuron& target);
    Neuron &getSource() const;
    Neuron &getTarget() const;
    double getWeight() const;
    void setWeight(double const weight);
    double getValue() const;
    double getWeighedValue() const;
    TrainingData *getTrainingData() const;
    void setTrainingData(TrainingData *const data);
    int const id;

  private:
    TrainingData *trainingData;
    Neuron *const source;
    Neuron *const target;
    double weight = 0.0;
  };
}

#endif
