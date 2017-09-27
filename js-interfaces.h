//
// Created by jefferson on 12/09/17.
//

#ifndef XGBOOST_JS_JS_INTERFACES_H
#define XGBOOST_JS_JS_INTERFACES_H

#include "xgboost/include/xgboost/c_api.h"

#include <utility>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

std::pair<BoosterHandle*, DMatrixHandle*>* create_model(float* dataset, float* labels, int rows, int cols);
void set_param(BoosterHandle* model, char* arg, char* value);
void train_full_model(float* dataset, float* labels, int samples, int dimensions, BoosterHandle* model, int iterations);
const float* predict(BoosterHandle* model, float* dataset, int samples, int dimensions);
void free_memory_model(BoosterHandle* model);

#ifdef __cplusplus
}
#endif

#endif //XGBOOST_JS_JS_INTERFACES_H
