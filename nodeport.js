// This is a scratchpad that I'm using so I can think about how the arduino should behave in a language I actually know
const Rx = require('rxjs/Rx');

const servoClock = 15;


function moveFromTo(servoName, start, end, duration) {
    const sequence = createMovementSequence(start, end, duration);

    doWhileOverTime(function(i){
        console.log(`${servoName} moves to ${Math.round(sequence[i])}`);
    }, sequence.length, servoClock);
}

moveFromTo('berend', 40, 50, 2000);

/*
    helper functions
*/

function createMovementSequence(start, end, duration) {
    let sequence = [start];
    const stepNums = Math.floor(duration / servoClock);
    const stepSize = (end - start) / stepNums;
    let currentVal = start;
    
    for (let i = 0; i < stepNums ; i++) {
        currentVal = currentVal + stepSize;
        sequence.push(currentVal);
     }

    return sequence;
}

function doWhileOverTime(fn, iterations, interval){
    let i = 0;
    
    const timer = setInterval(function(){
        fn(i);
        i ++;
        if (i == iterations) {
            clearInterval(timer);
        }
    }, interval);
}


// todo: rewrite to rxjs
// let berend = Rx.Observable.of(1,2,3);
// berend.subscribe(x => console.log(x));