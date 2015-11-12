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

#ifndef BRAINY_TRAININGSET_HPP
#define BRAINY_TRAININGSET_HPP

#include <iterator>
#include <cassert>
#include "brainy/training_pair.hh"

namespace brainy {
  class TrainingSet {
  public:
    virtual ~TrainingSet() {};
    virtual const TrainingPair &at(const size_t index) const = 0;
    virtual size_t size() const = 0;

    class const_iterator {
    public:
      const_iterator(const TrainingSet &set, size_t ptr) : set(set), ptr(ptr) {}
      const TrainingPair& operator*() const;
      const_iterator operator++();
      const_iterator operator++(int junk);
      bool operator==(const const_iterator& rhs);
      bool operator!=(const const_iterator& rhs);
    private:
      const TrainingSet &set;
      size_t ptr;
    };

    const_iterator begin() const;
    const_iterator end() const;
  };
}

#endif
