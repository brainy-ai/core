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

#include "brainy/TrainingSet.hpp"
#include "brainy/TrainingPair.hpp"
#include <iostream>

namespace brainy {
  const TrainingPair& TrainingSet::const_iterator::operator*() const {
    return set.at(ptr);
  }

  TrainingSet::const_iterator TrainingSet::const_iterator::operator++() {
    ptr++;
    return *this;
  }

  TrainingSet::const_iterator TrainingSet::const_iterator::operator++(int junk) {
    TrainingSet::const_iterator i = *this;
    ptr++;
    return i;
  }

  bool TrainingSet::const_iterator::operator==(const const_iterator& rhs) {
    return rhs.ptr == ptr;
  }

  bool TrainingSet::const_iterator::operator!=(const const_iterator& rhs) {
    return rhs.ptr != ptr;
  }

  TrainingSet::const_iterator TrainingSet::begin() const {
    return TrainingSet::const_iterator(*this, 0);
  }

  TrainingSet::const_iterator TrainingSet::end() const {
    return TrainingSet::const_iterator(*this, size());
  }
}
