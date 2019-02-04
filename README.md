# Welcome to **Self Localizator**, your new C++ library for detecting obstacles and self localization in space!
[![Build Status](https://travis-ci.org/BartekkPL/self-localizator.svg?branch=master)](https://travis-ci.org/BartekkPL/self-localizator)
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

This parser has been used only on Linux, but
it probably can works on any other platform as well, because it doesn't use Linux system library.

## Usage ##

The only thing what you have to do is build and link this library!
If you want to know something more please look at tests or write mail to me:)

### Build ###
```
git clone https://github.com/BartekkPL/self-localizator.git
cd self-localizator/
mkdir build
cd build/
cmake ..
make
```

And after these steps you have builded library ready to use it in new projects!

You found it at **self-localizator/build/libSelfLocalizator.so**.

## Projects using this library ##

I use it in my master thesis.

## License ##

SELF-LOCALIZATOR is released under [Apache License](https://opensource.org/licenses/Apache-2.0).
