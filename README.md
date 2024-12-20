# `BigInt`

By Andres Gomez\
Email: <gomezbaa@mcmaster.ca>\
GitHub: <https://github.com/AnfegoB>

This is the complete documentation

* [Introduction](#introduction)
    * [Motivation](#motivation)
    * [Contents](#Contents)
    * [Compiling and compatibility](#compiling-and-compatibility)
* [Getting started](#getting-started)
    * [Installing the library](#installing-the-library)
    * [Constructors](#constructors)
* [Testing the library](#testing-the-library)
    * [Automated tests](#automated-tests)


## Introduction

### Motivation

This class should be viewed as an extension of the usual C++ signed integer types, except that your class will allow signed integers of unlimited range - limited only by the computer's memory.

### Contents

* bigint.hpp: A header file containing the entire code for the class bigint. 

* test.cpp:  A program that comprehensively and thoroughly tests every single feature of your class to make sure it works properly.

### Compiling and compatibility
 This code should compile using the latest versions of GCC and/or Clang with the compiler arguments -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow -Wpedantic -std=c++23

 ## Getting started

### Installing the library

To install `BigInt`, simply download the latest release from the GitHub repository, place the header file `bigint.hpp` in the desired folder, and include it in your program:

```cpp
#include "bigint.hpp"
```
### Constructors

#### Default constructor

#### int64_t constructor

#### string constructor

### Available operators

#### Insertion

#### Comparison

#### Addition

#### Subtraction

#### Increment/Decrement 

#### Multiplication

## Additional functions

#### Exponentiation

#### Random bigint generation

## Testing the library

### Automated tests

The file `test.cpp` in the GitHub repository will perform automated tests of all aspects of the library. In addition, the code is meant to serve as an example of how to properly use the library.
