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

* bigint.hpp: A header file containing the entire code for the class bigint. Doxygen was employed and for each function and class there are comments explaining the input, output and relevant algorithms. 

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

## Complete library reference

This section provides a complete reference to classes, member functions and objects available in this library, along with other important information.

* Constructors:
    
    *`bigint()`: Default constructor creates the integer 0.
    *`bigint(int64_t &number_int64)`: Construct a new bigint object from a int64_t integer.  It takes the integer number as input. If it is zero creates the 0 bigint. If not, takes the magnitude and starts taking the digits from right to left and storing them in a vector<int64_t>. Depending on the sign the initial digit from the vector is selected 0: negative numbers, 1:positive numbers.
    *`bigint(const std::string &string_in)`: Construct a new bigint object from a string of digits. The constructor catches cases in which the argument given is not a number and throws an invalid argument error. A positive number can either be defined with or without the + symbol. A negative number requires the - symbol.
* Member functions:
    *`std::vector<uint8_t> get_vec()`: Gets the vector object corresponding to the digits. This is useful because then we can use the member functions of the vector class when overloading operators for the bigint class.
    *`bigint power(bigint &big_b)`: Exponentiation function, it gives the bigint number to the param big_b exponent. This is a rough algorithm for exponentiation, it employs the multiplication overload and performs the successive multiplications.
* Available operations:
    *`std::ostream &operator<<(std::ostream &out, const bigint &big_integ)`: Overload of the << operator. Makes use of the array containing the bigint digits by calling the get_vec() function.
    *`bool operator==(const bigint &lhs, const bigint &rhs)`: Overloading the == operator. This overload is slightly modified from the lecture notes (https://baraksh.com/CSE701/notes/) in the case of vectors (section 5.2.3). First the sizes between bigints are compared, as no two numbers with different number of digits can be equal. Then every digit is compared, as the first refers to the sign, it also accounts for it.
    *`bool operator!=(const bigint &lhs, const bigint &rhs)`: Overloading the != operator. It is just the negation of the == case.
    *`bool operator>(const bigint &lhs, const bigint &rhs)`: Overloading the > operator. First the signs are checked, all positive numbers are greater than all negative ones. Then the size of the left hand side is compared to siz of the right hand depending on the sign, and how close they are to 0. If the digits have the same amount of digits then every digit must be checked, from the most significant to the least one.
    *`bool operator>=(const bigint &lhs, const bigint &rhs)`: Overloading the >= operator.  Having == and >, then => is constructed employing the logical or.
    *`bool operator<(const bigint &lhs, const bigint &rhs)`: Overloading the < operator. Checks for greater than or equal and negates the result
    *`bool operator<=(const bigint &lhs, const bigint &rhs)`: Overloading the <= operator. Cannot negate the = here too, it can only be included in one of the overloads.
    *`bigint operator-(bigint big)`: Overloading the - (unary) operator. The unary negation operator acting on bigint, changes the first element of the array containing the digits.
    *`bigint& operator+=(bigint &lhs, bigint &rhs)`: Overloading the += operator. Initially it checks for a trivial sum. It checks for sign operations (-a + b = b - a) and (a-b calls -= ). If both numbers have the same sign then it sums the magnitudes and keeps the sign. It takes the number at the least significant position and if the length is shorter than the result use a 0 instead. Then it is summed, if the result is bigger or equal than 10 then 1 is carried and the last digit is stored in result.
    *`bigint operator+(bigint lhs, bigint rhs)`: Overloading the + operator. In this case the idea of overloading += first and then the + without reference is taken from the lecture notes.
    *`bigint &operator++(bigint &big)`: Overloading the pre-increment operator ++. It sums one and then returns the bigint.
    *`bigint operator++(bigint &big, int)`: Overloading the post-increment operator. It returns the bigint and then increments by one.
    *`bigint &operator-=(bigint &lhs, bigint &rhs)`: Overloading the -= operator. Initially it checks for a trivial sum. It checks for sign operations (a - (-b) = a + b) and (-a - ( - b ) = b - a). It only receives positive bigint integers, it uses += to receive the appropriate input. It cheeks if the rhs is bigger than the lhs and decides if the sign will be -.It takes the number at the least significant position and if the length is shorter than the result use a 0 instead. Then it subtracts them and subtracts the carry, if the result is below 0 then 1 is carried over and 10 is summed.
    *`bigint operator-(bigint lhs, bigint rhs)`: Overloading the - operator. In this case the idea of overloading -= first and then the + without reference is taken from the lecture notes.
    *`bigint& operator--(bigint& big)`: Overloading the pre-decrement operator --. It decrements by one and then returns the bigint.
    *`bigint operator--(bigint& big , int)`: Overloading the pre-decrement operator --. It returns the bigint and then decrements by one.
    *`bigint &operator*=(bigint &lhs, const bigint &rhs)`: Initially it checks for a trivial product. It checks for sign operations (-- = +) (-+ = -). It takes the digit from the lhs at the least significant position and iterates multiplying over all the digits of the rhs. After each multiplication it sums the carry and checks if the product is bigger than 10. If that is the case, takes the integer division as carry (most significant number) and the modulo as the resulting digit. This result is the first row, the next iteration is done employing the following significant digit (from right to left) from the lhs, in this case the same multiplication process is performed, and so forth for all the digits in lhs. After doing this, each row result is multiplied by 10^n where n is the row number, and then all of them are summed obtaining the final product.
    *`bigint operator*(bigint lhs, const bigint &rhs)`: Overloading the * operator. In this case the idea of overloading *= first and then the * without reference is taken from the lecture notes.
* Additional functions:
    **`bigint random_bigint(size_t const &num_digits)`: Generates a random bigint number from a given number of digits





    
    

    