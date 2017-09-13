module.exports = function (xgboost) {
    /* eslint-disable camelcase */
    const hi = xgboost.cwrap('hello_world', 'number');
    /*const predict_one_probability = xgboost.cwrap('libsvm_predict_one_probability', 'number', ['number', 'array', 'number', 'number']);
    const add_instance = xgboost.cwrap('add_instance', null, ['number', 'array', 'number', 'number', 'number']);
    const create_svm_nodes = xgboost.cwrap('create_svm_nodes', 'number', ['number', 'number']);
    const train_problem = xgboost.cwrap('libsvm_train_problem', 'number', ['number', 'string']);
    const svm_get_nr_sv = xgboost.cwrap('svm_get_nr_sv', 'number', ['number']);
    const svm_get_nr_class = xgboost.cwrap('svm_get_nr_class', 'number', ['number']);
    const svm_get_sv_indices = xgboost.cwrap('svm_get_sv_indices', null, ['number', 'number']);
    const svm_get_labels = xgboost.cwrap('svm_get_labels', null, ['number', 'number']);
    const svm_free_model = xgboost.cwrap('svm_free_model', null, ['number']);
    const svm_cross_validation = xgboost.cwrap('libsvm_cross_validation', null, ['number', 'string', 'number', 'number']);
    const free_problem = xgboost.cwrap('free_problem', null, ['number']);
    const serialize_model = xgboost.cwrap('serialize_model', 'number', ['number']);
    const deserialize_model = xgboost.cwrap('deserialize_model', 'number', ['string']);*/

    /* eslint-enable camelcase */

    class XGBoost {
        static hello() {
            var d = hi();
            console.log(d);
        }
    }

    return XGBoost;
};
