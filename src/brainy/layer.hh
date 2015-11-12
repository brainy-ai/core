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
#include "brainy/neuron.hh"

namespace brainy {
  class ActivationFunction;

  class Layer {
  public:
    Layer(size_t const neurons);
    Layer(size_t const neurons, ActivationFunction* const activation);
    Layer(size_t const neurons, ActivationFunction* const activation, bool const bias);
    Neuron& neuron(size_t const index) const;
    std::vector<Neuron*>& getNeurons();
    static void interconnect(Layer& source, Layer& target);
    void activate();
    bool hasBias() const;
    ActivationFunction *getActivation() const;

  private:
    ActivationFunction *activation;
    void init(size_t const neurons, ActivationFunction* const activation, bool const bias);
    std::vector<Neuron*> neurons;
  };
}

#endif
