#include "brainy/trainer/Trainer.hpp"
#include "brainy/trainer/Momentum.hpp"
#include "brainy/trainer/LearningRate.hpp"
#include "brainy/TrainingData.hpp"
#include "brainy/TrainingSet.hpp"
#include "brainy/network/FeedForward.hpp"

#include <vector>

namespace brainy {
  class Neuron;

  class BackPropagation : public Trainer, public Momentum, public LearningRate {
  public:
    BackPropagation(FeedForward& network, TrainingSet& set) : Trainer(network, set) {};
    void setBatchSize(const int size);
    int getBatchSize();
    void preTrain();
    void epoch();

  private:
    int batchSize = 0;
    void propagate(std::vector<double> patternError);
    void calculateOutputDeltas(std::vector<double> patternError);
    void calculateInternalDeltas();
    void updateNeuronWeights(Neuron* neuron);
    void applyBatchChanges();

    struct BPTrainingData : public TrainingData {
      double delta = 0.0;
      double lastChange = 0.0;
      double flatSpotFix = 0.0;
    };

    struct BPConnectionData : public TrainingData {
      double change = 0.0;
    };
  };
}
