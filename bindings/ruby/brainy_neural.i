%module "brainy::neural"
%{
#include "../../include/brainy/neural/activation/ActivationFunction.hpp"
#include "../../include/brainy/neural/activation/Sigmoid.hpp"
%}

%include "../../include/brainy/neural/activation/ActivationFunction.hpp"
%include "../../include/brainy/neural/activation/Sigmoid.hpp"
