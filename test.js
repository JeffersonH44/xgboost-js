async function exec() {
    let XGBoost = await require('./wasm');
    var trainer = new XGBoost();
    trainer.free();
    return "end of execution!";
}

exec().then((result) => {
    console.log(result);
});