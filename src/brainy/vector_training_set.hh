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

#ifndef BRAINY_VECTORTRAININGSET_HPP
#define BRAINY_VECTORTRAININGSET_HPP

#include "brainy/training_set.hh"

namespace brainy {
  class VectorTrainingSet : public TrainingSet {
  public:
    void add(std::vector<double> input, std::vector<double> ideal);
    const TrainingPair &at(const size_t index) const;
    size_t size() const;

  private:
    std::vector<TrainingPair> data;
  };
}

#endif
