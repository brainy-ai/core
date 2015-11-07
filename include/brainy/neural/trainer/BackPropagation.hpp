#include "brainy/neural/trainer/Trainer.hpp"
#include "brainy/neural/trainer/Momentum.hpp"
#include "brainy/neural/trainer/LearningRate.hpp"
#include "brainy/neural/TrainingData.hpp"
#include "brainy/neural/network/FeedForward.hpp"

#include <vector>

namespace brainy {
  namespace neural {
    class Neuron;

    class BackPropagation : public Trainer, public Momentum, public LearningRate {
    public:
      BackPropagation(FeedForward& network) : Trainer(network) {};
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

      struct TrainingData : public neural::TrainingData {
        double delta = 0.0;
        double lastChange = 0.0;
        double flatSpotFix = 0.0;
      };

      struct ConnectionData : public neural::TrainingData {
        double change = 0.0;
      };
    };
  }
}
