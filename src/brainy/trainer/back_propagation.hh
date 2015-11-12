#include "brainy/trainer/trainer.hh"
#include "brainy/trainer/momentum.hh"
#include "brainy/trainer/learning_rate.hh"
#include "brainy/training_data.hh"
#include "brainy/training_set.hh"
#include "brainy/network/feed_forward.hh"

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
