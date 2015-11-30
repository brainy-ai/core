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

#ifndef BRAINY_TRAINER_GOAL_HH
#define BRAINY_TRAINER_GOAL_HH

namespace brainy {
  class Goal {
  public:
    virtual ~Goal() {};
    inline void setGoal(const double goal) {
      this->goal = goal;
    }
    inline double getGoal() const {
      return goal;
    }
  private:
    double goal = 0.05;
  };
}

#endif
