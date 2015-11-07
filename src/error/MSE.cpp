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

#include "brainy/neural/error/MSE.hpp"
#include <cassert>

namespace brainy {
  namespace neural {
    std::vector<double> MSE::calculate(const std::vector<double> actual, const std::vector<double> expected) {
      assert(actual.size() == expected.size());

      std::vector<double> result(actual.size());

      for (int i = 0; i < actual.size(); i++) {
        result[i] = expected[i] - actual[i];
        totalError += result[i] * result[i];
      }

      patternCount++;

      return result;
    }

    double MSE::getResult() {
      return totalError / (2.0 * patternCount);
    }
  }
}
