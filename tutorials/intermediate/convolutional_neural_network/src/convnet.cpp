// Copyright 2019 Markus Fleischhacker
#include "convnet.h"
#include <torch/torch.h>

ConvNetImpl::ConvNetImpl(int64_t num_classes)
    : fc(7 * 7 * 32, num_classes) {
    register_module("layer1", layer1);
    register_module("layer2", layer2);
    register_module("fc", fc);
}

torch::Tensor ConvNetImpl::forward(torch::Tensor x) {
    x = layer1->forward(x);
    x = layer2->forward(x);
    x = x.view({-1, 7 * 7 * 32});
    x = fc->forward(x);
    return torch::log_softmax(x, 1);
}
