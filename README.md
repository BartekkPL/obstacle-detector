# Welcome to **Obstacle Detector**, your new C++ library for detecting obstacles in space with only one camera!
[![Build Status](https://travis-ci.org/BartekkPL/obstacle-detector.svg?branch=master)](https://travis-ci.org/BartekkPL/obstacle-detector)
=======================

  - [Features](#features)
  - [Platforms](#platforms)
  - [Usage](#usage)
    - [Build](#build)
  - [Projects using this library](#projexts-using-this-bibrary)
  - [License](#license)

## Features ##

  * Logs from working provided by [**easyloging++**](https://github.com/muflihun/easyloggingpp)
  * Tested via [**Google Test**](https://github.com/google/googletest) framework

## Platforms ##

This obstacle detector has been used only on Linux, but
it probably can works on any other platform as well.

Tested on Raspberry Pi 3B+.

## Usage ##

The only thing what you have to do is build and link this library!
If you want to know something more please look at tests or write mail to me:)

### Build ###
```
git clone https://github.com/BartekkPL/obstacle-detector.git
cd obstacle-detector/
mkdir build
cd build/
cmake ..
make
```

And after these steps you have builded library ready to use it in new projects!

You found it at **obstacle-detector/build/libObstacleDetector.so**.

## Projects using this library ##

I use it in my master thesis.

## License ##

OBSTACLE-DETECTOR is released under [Apache License](https://opensource.org/licenses/Apache-2.0).
