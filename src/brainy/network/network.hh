#ifndef BRAINY_NEURAL_NETWORK_NETWORK_HPP
#define BRAINY_NEURAL_NETWORK_NETWORK_HPP

#include <vector>
#include <vector>

namespace brainy {
  class Network {
  public:
    virtual void activate() = 0;
    virtual void setInput(const std::vector<double> &input) = 0;
    virtual std::vector<double> getOutput() const = 0;
    virtual void finalize() {};
  };
}

#endif
