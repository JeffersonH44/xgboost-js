//
// Created by jefferson on 12/09/17.
//
#include "js-interfaces.h"

Model create_model(float* dataset, float* labels, int rows, int cols) {
    BoosterHandle* model = new BoosterHandle();
    DMatrixHandle* h_train = new DMatrixHandle();
    XGDMatrixCreateFromMat(dataset, rows, cols, -1, h_train);
    XGDMatrixSetFloatInfo(*h_train, "label", labels, rows);
    XGBoosterCreate(h_train, 1, model);

    return new std::pair<BoosterHandle*, DMatrixHandle*>(model, h_train);
}

void set_param(Model model, char* arg, char* value) {
    XGBoosterSetParam(*(model->first), arg, value);
}

void train_full_model(Model model, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        XGBoosterUpdateOneIter(*(model->first), i, *(model->second));
    }
}

const float* predict(Model model, float* dataset, int samples, int dimensions) {
    DMatrixHandle h_test;
    XGDMatrixCreateFromMat(dataset, samples, dimensions, -1, &h_test);
    bst_ulong out_len;
    const float *f;
    XGBoosterPredict(*(model->first), h_test, 0, 0, &out_len, &f);
    XGDMatrixFree(h_test);

    return f;
}

void free_memory_model(Model model) {
    XGBoosterFree(*(model->first));
    XGDMatrixFree(*(model->second));
    delete model;
}
