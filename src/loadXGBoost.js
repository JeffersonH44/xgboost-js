module.exports = function (xgboost) {
    /* eslint-disable camelcase */
    const create_model = xgboost.cwrap('create_model', 'number');
    const free_model = xgboost.cwrap('free_memory_model', null);
    const set_param = xgboost.cwrap('set_param', null, ['number', 'string', 'string']);
    const train = xgboost.cwrap('train', null, ['array', 'array', 'number', 'number', 'number', 'number']);

    /* eslint-enable camelcase */

    const defaultOptions = {
        "objective": "reg:linear",
        "learning_rate": "0.1",
        "n_estimators": "10",
        "max_depth": "3"
    };

    class XGBoost {
        constructor(options) {
            this.model = create_model();
            console.log("model created...");
            var variables = Object.keys(defaultOptions);
            for(var i = 0; i < variables.length; ++i) {
                var variable = variables[i];
                var value = defaultOptions[variable];
                set_param(this.model, variable, value);
            }
        }

        free() {
            console.log("free");
            free_model(this.model);
        }
    }

    return XGBoost;
};
