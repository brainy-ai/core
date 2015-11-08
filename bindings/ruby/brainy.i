%module "brainy"
%{
#include "../../include/brainy/Connection.hpp"
#include "../../include/brainy/Layer.hpp"
#include "../../include/brainy/Neuron.hpp"
#include "../../include/brainy/TrainingData.hpp"
#include "../../include/brainy/TrainingPair.hpp"
#include "../../include/brainy/Util.hpp"

#include "../../include/brainy/activation/ActivationFunction.hpp"
#include "../../include/brainy/activation/Linear.hpp"
#include "../../include/brainy/activation/Sigmoid.hpp"
#include "../../include/brainy/activation/Tanh.hpp"

#include "../../include/brainy/error/ErrorFunction.hpp"
#include "../../include/brainy/error/MSE.hpp"
#include "../../include/brainy/error/RMS.hpp"

#include "../../include/brainy/network/Network.hpp"
#include "../../include/brainy/network/FeedForward.hpp"

#include "../../include/brainy/randomize/Randomize.hpp"
#include "../../include/brainy/randomize/BasicRandomize.hpp"

#include "../../include/brainy/trainer/Trainer.hpp"
#include "../../include/brainy/trainer/LearningRate.hpp"
#include "../../include/brainy/trainer/Momentum.hpp"
#include "../../include/brainy/trainer/BackPropagation.hpp"

#include "../../include/brainy/trainer/plugin/TrainerPlugin.hpp"
#include "../../include/brainy/trainer/plugin/SmartLearningRate.hpp"
#include "../../include/brainy/trainer/plugin/SmartMomentum.hpp"
#include "../../include/brainy/trainer/plugin/Monitor.hpp"
%}

%include "../../include/brainy/Connection.hpp"
%include "../../include/brainy/Layer.hpp"
%include "../../include/brainy/Neuron.hpp"
%include "../../include/brainy/TrainingData.hpp"
%include "../../include/brainy/TrainingPair.hpp"
%include "../../include/brainy/Util.hpp"

%include "../../include/brainy/activation/ActivationFunction.hpp"
%include "../../include/brainy/activation/Linear.hpp"
%include "../../include/brainy/activation/Sigmoid.hpp"
%include "../../include/brainy/activation/Tanh.hpp"

%include "../../include/brainy/error/ErrorFunction.hpp"
%include "../../include/brainy/error/MSE.hpp"
%include "../../include/brainy/error/RMS.hpp"

%include "../../include/brainy/network/Network.hpp"
%include "../../include/brainy/network/FeedForward.hpp"

%include "../../include/brainy/randomize/Randomize.hpp"
%include "../../include/brainy/randomize/BasicRandomize.hpp"

%include "../../include/brainy/trainer/Trainer.hpp"
%include "../../include/brainy/trainer/LearningRate.hpp"
%include "../../include/brainy/trainer/Momentum.hpp"
%include "../../include/brainy/trainer/BackPropagation.hpp"

%include "../../include/brainy/trainer/plugin/TrainerPlugin.hpp"
%include "../../include/brainy/trainer/plugin/SmartLearningRate.hpp"
%include "../../include/brainy/trainer/plugin/SmartMomentum.hpp"
%include "../../include/brainy/trainer/plugin/Monitor.hpp"
