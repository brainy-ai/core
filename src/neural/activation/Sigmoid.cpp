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

#include "brainy/neural/activation/Sigmoid.hpp"
#include <cmath>

namespace brainy {
  namespace neural {
    double Sigmoid::primary(const double input) {
      return 1.0 / (1.0 + exp(alpha * -input));
    }

    double Sigmoid::derivative(const double output) {
      return (alpha * (1.0 - output) * output);
    }

    bool Sigmoid::hasFlatSpot() {
      return true;
    }

    void Sigmoid::setAlpha(const double alpha) {
      this->alpha = alpha;
    }
  }
}
