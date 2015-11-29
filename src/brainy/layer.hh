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

#ifndef BRAINY_LAYER_HH
#define BRAINY_LAYER_HH

#include <vector>
#include <cassert>

namespace brainy {
  class Layer {
  public:
    Layer(size_t const neurons);
    virtual ~Layer() {};
    virtual void activate() {};
    virtual void derivative() {};
    inline size_t getNeurons() {
      return neurons;
    }
    std::vector<double> &getOutput();
    std::vector<double> &getDerivatives();

    inline double getInput() {
      double sum = 0;
      if (prevLayer == nullptr) {
        for (auto x : getOutput()) {
          sum += x;
        }
      } else {
        for (auto x : prevLayer->getOutput()) {
          sum += x;
        }
      }

      return sum;
    }

    inline size_t inputsPerNeuron() {
      //assert(prevLayer != nullptr);
      if (prevLayer == nullptr) {
        return 1; // input layer ????????????
      }
      return prevLayer->getNeurons();
    }

    inline double getWeight(size_t const neuron, size_t const input) {
      return weight[neuron * inputsPerNeuron() + input];
    }
    inline void setWeight(size_t const neuron, size_t const input, double const value) {
      weight[neuron * inputsPerNeuron() + input] = value;
    }
    void setPrevLayer(Layer &layer);

  protected:
    size_t const neurons;
    std::vector<double> output;
    std::vector<double> weight;
    std::vector<double> derivatives;
    Layer *prevLayer;
  };
}

#endif
