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

#ifndef BRAINY_ACTIVATION_SIGMOID_HH
#define BRAINY_ACTIVATION_SIGMOID_HH

#include "brainy/activation/activation_function.hh"

namespace brainy {
  class Sigmoid : public ActivationFunction {
  public:
    double primary(const double input) const override;
    double derivative(const double output) const override;
    bool hasFlatSpot() const override;
    double getFlatSpotFix() const override;
    void setAlpha(const double alpha);

  private:
    double alpha = 1.0;
  };
}

#endif
