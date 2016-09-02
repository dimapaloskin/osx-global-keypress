var Spy = require('./index');

var spy = new Spy();
spy.start();

spy.on('press', (data) => {

  console.log(data);
});

spy.on('error', (error) => {

  console.log(error);
});

spy.on('close', () => {

  console.log('closed');
});

setTimeout(function() {
  spy.stop();
}, 2000)
