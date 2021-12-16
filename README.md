# osx-global-keypress

Global key press event handler for OS X (Mac Os).

This is a fork that emits flags too, allowing you to identify if special keys
like shift and command are pressed. Check [this
link](https://developer.apple.com/documentation/coregraphics/cgeventflags) for a
list of supported flags.

It also emits mouse down events, with -1 being left, -2 being right and -3 being
middle button.

## Install

```shell
npm i --save osx-global-keypress
```

## Usage

See test.js example

**Important:** you need use "sudo" for running your js scripts which use osx-global-keypress module.

MIT © [Dmitry Pavlovsky](http://paloskin.me)
