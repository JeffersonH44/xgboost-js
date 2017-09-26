'use strict';

const loadXGBoost = require('./src/loadXGBoost');
const xgboost = require('./dist/asm/xgboost');
module.exports = loadXGBoost(xgboost);