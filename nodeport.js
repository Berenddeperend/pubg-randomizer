// This is a scratchpad that I'm using so I can think about how the arduino should behave in a language I actually know
const Rx = require('rxjs/Rx');

const servoClock = 100;

//Doet zijn magie in 1x, ipv over time
function moveSingleWithSpeed(servo, start, end, duration){
    let stepNums = duration / servoClock;    
    let stepSize = (end - start) / stepNums;
    let currentVal = start;

    for (let i = 0; i < stepNums ; i++) {
        currentVal = currentVal + stepSize;
        console.log(`${servo} should go to ${currentVal}`);
     }
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

doWhileOverTime(function(i){
    console.log('im executing!' + i);    
}, 15, 100);


// let berend = Rx.Observable.of(1,2,3);
// berend.subscribe(x => console.log(x));


// moveSingleWithSpeed('Berend', 0, 100, 200);


// todo: omschrijven naar rxjs stream
// todo: omschrijven naar ES6 oplossing

