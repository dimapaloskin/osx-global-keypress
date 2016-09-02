var spawn = require('child_process').spawn;
var util = require('util');
var events = require('events');

function Spy() {

  this.isSpawned = false;
  this.proc = null;
}

util.inherits(Spy, events.EventEmitter);

Spy.prototype.start = function() {

  this.proc = spawn('./bin/globalkeypress-daemon');
  this.isSpawned = true;

  this.proc.stdout.on('data', function(data) {

    this.emit('press', {
      code: parseInt(data.toString(), 10)
    });
  }.bind(this));

  this.proc.stderr.on('data', function(data) {

    this.emit('error', data.toString());
  }.bind(this));

  this.proc.on('close', function(code) {

    this.emit('close', code);
  }.bind(this));
}

Spy.prototype.stop = function() {

  if (!this.proc) {
    return;
  }

  this.proc.kill();
  this.isSpawned = false;
}

Spy.prototype.isRunning = function() {
  return this.isSpawned;
}

module.exports = Spy;
