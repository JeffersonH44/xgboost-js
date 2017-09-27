//
// Created by jeffersonhernandez on 9/27/17.
//

#include <iostream>
#include <utility>

#include "xgboost/include/xgboost/c_api.h"
#include "js-interfaces.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;

int main() {
    // create the train data
    int cols=3,rows=5;
    float train[rows][cols];
    for (int i=0;i<rows;i++)
        for (int j=0;j<cols;j++)
            train[i][j] = (i+1) * (j+1);

    float train_labels[rows];
    for (int i=0;i<rows;i++)
        train_labels[i] = 1+i*i*i;


    // convert to DMatrix
    /*DMatrixHandle h_train[1];
    XGDMatrixCreateFromMat((float *) train, rows, cols, -1, &h_train[0]);

    // load the labels
    XGDMatrixSetFloatInfo(h_train[0], "label", train_labels, rows);

    // read back the labels, just a sanity check
    bst_ulong bst_result;
    const float *out_floats;
    XGDMatrixGetFloatInfo(h_train[0], "label" , &bst_result, &out_floats);
    for (unsigned int i=0;i<bst_result;i++)
        cout << "label[" << i << "]=" << out_floats[i] << endl;*/

    Model model = create_model((float *) train, train_labels, rows, cols);

    // create the booster and load some parameters
    //BoosterHandle* h_booster = model->first;
    //DMatrixHandle* h_train = model->second;

    set_param(model, "booster", "gbtree");
    set_param(model, "objective", "reg:linear");
    set_param(model, "max_depth", "5");
    set_param(model, "eta", "0.1");
    set_param(model, "min_child_weight", "1");
    set_param(model, "subsample", "0.5");
    set_param(model, "colsample_bytree", "1");
    set_param(model, "num_parallel_tree", "1");

    // perform 200 learning iterations
    train_full_model(model, 200);

    // predict
    const int sample_rows = 5;
    float test[sample_rows][cols];
    for (int i=0;i<sample_rows;i++)
        for (int j=0;j<cols;j++)
            test[i][j] = (i+1) * (j+1);
    /*DMatrixHandle h_test;
    XGDMatrixCreateFromMat((float *) test, sample_rows, cols, -1, &h_test);
    const float *f;
    XGBoosterPredict(h_booster, h_test, 0,0,&out_len,&f);*/
    const float *f = predict(model, (float *) test, sample_rows, cols);

    for (unsigned int i=0;i<sample_rows;i++)
        cout << "prediction[" << i << "]=" << f[i] << endl;


    // free xgboost internal structures
    /*XGDMatrixFree(h_train[0]);
    XGDMatrixFree(h_test);
    XGBoosterFree(h_booster);*/
    free_memory_model(model);
    cout << "finished";
    return 0;
}

#ifdef __cplusplus
}
#endif