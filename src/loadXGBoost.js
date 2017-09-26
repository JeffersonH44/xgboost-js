module.exports = function (xgboost) {
    /* eslint-disable camelcase */
    const create_model = xgboost.cwrap('create_model', 'number');
    const free_model = xgboost.cwrap('free_memory_model', null);
    const set_param = xgboost.cwrap('set_param', null, ['number', 'string', 'string']);

    /* eslint-enable camelcase */

    class XGBoost {
        constructor(options) {
            this.model = create_model();
            //console.log("js pointer", this.model);
            set_param(this.model, "objective", "reg:linear");
        }

        free() {
            free_model(this.model);
        }
    }

    return XGBoost;
};
