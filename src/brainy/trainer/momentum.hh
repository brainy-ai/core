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

#ifndef BRAINY_NEURAL_TRAINER_MOMENTUM_HPP
#define BRAINY_NEURAL_TRAINER_MOMENTUM_HPP

namespace brainy {
  class Momentum {
  public:
    virtual ~Momentum() {};
    void setMomentum(const double momentum);
    double getMomentum() const;
  private:
    double momentum = 0.0;
  };
}

#endif
