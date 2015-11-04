%module "brainy"
%{
%}

%module "brainy::neural::activation"
%{
#include "brainy/neural/activation/Base.hpp"
#include "brainy/neural/activation/Sigmoid.hpp"
%}

%include "../../../../include/brainy/neural/activation/Base.hpp"
%include "../../../../include/brainy/neural/activation/Sigmoid.hpp"
