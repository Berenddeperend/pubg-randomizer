// This is a scratchpad that I'm using so I can think about how the arduino should behave in a language I actually know
const Rx = require('rxjs/Rx');

const servoClock = 10;

function createMovementSequence(start, end, duration) {
    let sequence = [];
    let stepNums = duration / servoClock;    
    let stepSize = (end - start) / stepNums;
    let currentVal = start;
    
    for (let i = 0; i < stepNums ; i++) {
        currentVal = currentVal + stepSize;
        sequence.push(currentVal);
     }

    return sequence;
}

function doWhileOverTime(fn, iterations, interval){
    let i = 0;
    
    let timer = setInterval(function(){
        fn(i);
        i ++;
        if (i == iterations) {
            clearInterval(timer);
        }
    }, interval);
}

function moveFromTo(servoName, start, end, duration) {
    let sequence = createMovementSequence(start, end, duration);

    doWhileOverTime(function(i){
        console.log(`${servoName} moves to ${sequence[i]}`);
    }, sequence.length, servoClock);
}

moveFromTo('berend', 40, 2000, 8000);



// todo: omschrijven naar rxjs stream
// todo: omschrijven naar ES6 oplossing

// let berend = Rx.Observable.of(1,2,3);
// berend.subscribe(x => console.log(x));