async function exec() {
    let XGBoost = await require('./wasm');
    XGBoost.hello();
    return "end of execution!";
}

exec().then((result) => {
    console.log(result);
});