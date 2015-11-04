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

#include "brainy/util.hpp"
#include <sys/time.h>
#include <random>
#include <iostream>

namespace brainy {
  namespace util {
    unsigned long long microtime() {
      struct timeval time;
      gettimeofday(&time, NULL);
      return ((unsigned long long)time.tv_sec * 1000000) + time.tv_usec;
    }

    double randomWeight() {
      static std::random_device rd;
      static std::mt19937 gen(rd());
      static std::uniform_real_distribution<> dis(-0.5, 0.5);
      return dis(gen);
    }

    double random(double min, double max) {
      //static std::random_device rd;
      static std::default_random_engine rd;
      rd.seed(1);
      static std::mt19937 gen(rd());
      std::uniform_real_distribution<> dis(min, max);
      return dis(gen);
    }

    void print(std::vector<double> data) {
      for (int i = 0; i < data.size(); i++) {
        std::cout << "vector[" << i << "] = " << data[i] << std::endl;
      }
    }

    int id() {
      static std::atomic<int> id(1);
      return ++id;
    }
  }
}
