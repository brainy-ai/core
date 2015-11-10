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

#include "brainy/randomize/basic_randomize.h"
#include "brainy/network/feed_forward.h"
#include "brainy/util.h"

namespace brainy {
  void BasicRandomize::randomize(FeedForward &net) {
    for (auto layer : net.getLayers()) {
      for (auto neuron : layer->getNeurons()) {
        for (auto conn : neuron->getOutputs()) {
          conn->setWeight(util::random(-0.5, 0.5));
        }
      }
    }
  }
}
