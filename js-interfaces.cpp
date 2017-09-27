//
// Created by jefferson on 12/09/17.
//
#include "js-interfaces.h"

std::pair<BoosterHandle*, DMatrixHandle*>* create_model(float* dataset, float* labels, int rows, int cols) {
    BoosterHandle* model = new BoosterHandle();
    DMatrixHandle* h_train = new DMatrixHandle();
    XGDMatrixCreateFromMat(dataset, rows, cols, -1, h_train);
    XGDMatrixSetFloatInfo(*h_train, "label", labels, rows);
    XGBoosterCreate(h_train, 1, model);

    return new std::pair<BoosterHandle*, DMatrixHandle*>(model, h_train);
}

void set_param(BoosterHandle* model, char* arg, char* value) {
    printf("setting param...");
    XGBoosterSetParam(*model, arg, value);
}

void train_full_model(float* dataset, float* labels, int samples, int dimensions, BoosterHandle* model, int iterations) {
    DMatrixHandle h_train[1];
    XGDMatrixCreateFromMat(dataset, samples, dimensions, -1, &h_train[0]);
    XGDMatrixSetFloatInfo(h_train[0], "label", labels, samples);
    XGBoosterCreate(h_train, 1, model);

    for (int i = 0; i < iterations; ++i) {
        XGBoosterUpdateOneIter(*model, i, h_train[0]);
    }

    XGDMatrixFree(h_train[0]);
}

const float* predict(BoosterHandle* model, float* dataset, int samples, int dimensions) {
    DMatrixHandle h_test;
    XGDMatrixCreateFromMat(dataset, samples, dimensions, -1, &h_test);
    bst_ulong out_len;
    const float *f;
    XGBoosterPredict(*model, h_test, 0, 0, &out_len, &f);
    XGDMatrixFree(h_test);

    return f;
}

void free_memory_model(BoosterHandle* model) {
    XGBoosterFree(*model);
}
