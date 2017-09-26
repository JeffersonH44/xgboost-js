async function exec() {
    let XGBoost = await require('./asm');
    var trainer = new XGBoost();
    trainer.free();
    return "end of execution!";
}

exec().then((result) => {
    console.log(result);
});