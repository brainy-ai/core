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

#ifndef BRAINY_ERROR_ERRORFUNCTION_HH
#define BRAINY_ERROR_ERRORFUNCTION_HH

#include <vector>

namespace brainy {
  class ErrorFunction {
  public:
    void reset();
    virtual std::vector<double> calculate(const std::vector<double> &actual,
                                          const std::vector<double> &expected) = 0;
    virtual double getResult() const = 0;

  protected:
    double totalError = 0.0;
    int patternCount = 0;
  };
}

#endif
