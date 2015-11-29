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

#include "brainy/layer.hh"
#include "brainy/activation/linear.hh"
#include "brainy/util.hh"

#include <cstddef>

namespace brainy {
  Layer::Layer(size_t const neurons) : neurons(neurons ){
    output.resize(neurons, 0.0);
    derivatives.resize(neurons, 0.0);
  }

  std::vector<double> &Layer::getOutput() {
    return output;
  }

  std::vector<double> &Layer::getDerivatives() {
    return derivatives;
  }

  void Layer::setPrevLayer(Layer &layer) {
    prevLayer = &layer;

    weight.resize(output.size() * prevLayer->getOutput().size(), brainy::util::randomWeight());
  }
}
