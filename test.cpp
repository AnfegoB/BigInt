#include <stdexcept>
#include "bigint.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>
//#include <cinttypes>
// #include <cmath>
// ========================================
// Test program for the bigint class
// ========================================

/**
 *
 * @brief Obtain an ordered pair of two distinct random numbers in a specified range.
 *This function is taken and modified from (https://github.com/bshoshany/thread-pool)
 * @param min The minimum value of the range.
 * @param max The maximum value of the range. Must be larger than `min`.
 * @return The random numbers.
 *
 */

std::pair<int64_t, int64_t> random_pair(int64_t min, int64_t max)
{
  static std::random_device rand_device;
  static std::mt19937_64 twister(rand_device());
  std::uniform_int_distribution<int64_t> dist(min, max);
  int64_t first = dist(twister);
  int64_t second;
  do
  {
    second = dist(twister);
  } while (second == first);
  if (second < first)
    return {second, first};
  return {first, second};
}

int main()
{
  std::cout << "========================================" << "\n";
  std::cout << "Test program for the bigint class (bigint.hpp)" << "\n";
  std::cout << "2024 Andres Gomez (gomezbaa@mcmaster.ca)" << "\n";
  std::cout << "========================================" << "\n";
  std::cout << "\n";

  std::cout << "Testing the default constructor (and the << overload)" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  bigint default_constructor;
  std::cout << "default_constructor: \n"
            << default_constructor << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";

  std::cout << "Testing the int64_t constructor" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  int64_t int64_t_n = 12345678987654321;
  int64_t int64_t_negative = -12345678987654321;
  int64_t int64_t_zero = 0;
  bigint int64_t_construct(int64_t_n);
  bigint int64_t_construct_negative(int64_t_negative);
  bigint int64_t_construct_zero(int64_t_zero);
  std::cout << "int64_t_construct: \n"
            << int64_t_construct << "\n";
  std::cout << "\n";
  std::cout << "int64_t_construct_negative: \n"
            << int64_t_construct_negative << "\n";
  std::cout << "\n";
  std::cout << "int64_t_construct_zero: \n"
            << int64_t_construct_zero << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";

  std::cout << "Testing the string constructor" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  bigint string_constructor("5544332211");
  bigint string_constructor_n("-5544332211");

  std::cout << "string_constructor: \n"
            << string_constructor << "\n";
  std::cout << "string_constructor_negative: \n"
            << string_constructor_n << "\n";

  std::cout << "string_constructor_invalid: using -5544aa22b1 \n";
  try
  {
    bigint string_not_valid("-5544aa22b1");
    std::cout << "string_not_valid: \n"
              << string_not_valid << "\n";
    std::cout << "\n";
  }
  catch (const std::invalid_argument &e)
  {
    std::cout << "Error: " << e.what() << '\n';
  }
  std::cout << "------------------------------------------------------";
  std::cout << "\n";
  std::cout << "\n";
  std::cout << "The << overload has already been employed " << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";

  std::cout << "Testing the overload of the == and != operator" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  bigint equal_a("9223372036854775807000"); // This number is bigger than the maximum int64_t
  bigint equal_b("9223372036854775807000");
  bigint equal_c("123");
  bigint equal_d("-123");
  bigint equal_e("0");

  std::cout << "9223372036854775807000 == 9223372036854775807000: \n"
            << std::boolalpha << (equal_a == equal_b) << "\n";
  std::cout << "\n";
  std::cout << "9223372036854775807000 == 123: \n"
            << std::boolalpha << (equal_a == equal_c) << "\n";
  std::cout << "\n";
  std::cout << "9223372036854775807000 != 123: \n"
            << std::boolalpha << (equal_a != equal_c) << "\n";
  std::cout << "\n";
  std::cout << "9223372036854775807000 != 9223372036854775807000: \n"
            << std::boolalpha << (equal_a != equal_b) << "\n";
  std::cout << "\n";
  std::cout << "123 != -123: \n"
            << std::boolalpha << (equal_c != equal_d) << "\n";
  std::cout << "\n";
  std::cout << "9223372036854775807000 != 0: \n"
            << std::boolalpha << (equal_a != equal_e) << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";

  std::cout << "Testing the overload of the > , < , >= and <= operators" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  bigint c("123");
  bigint d("-123");
  bigint e("200");
  bigint h("201");
  std::cout << "123 > -123: \n"
            << std::boolalpha << (c > d) << "\n";
  std::cout << "\n";
  std::cout << "123 < 123: \n"
            << std::boolalpha << (c < c) << "\n";
  std::cout << "\n";
  std::cout << "-123 > 123: \n"
            << std::boolalpha << (d > c) << "\n";
  std::cout << "\n";
  std::cout << "-123 < 123:: \n"
            << std::boolalpha << (d < c) << "\n";
  std::cout << "\n";
  std::cout << "201 >= 201: \n"
            << std::boolalpha << (h >= h) << "\n";
  std::cout << "\n";
  std::cout << "201 > 200: \n"
            << std::boolalpha << (h > e) << "\n";
  std::cout << "\n";
  std::cout << "201 <= 200: \n"
            << std::boolalpha << (h <= e) << "\n";
  std::cout << "\n";
  std::cout << "201 <= 201: \n"
            << std::boolalpha << (h <= h) << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";

  std::cout << "Testing the overload of the - (unary) operator" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "-(123): \n"
            << (-c) << "\n";
  std::cout << "\n";
  std::cout << "-(-123): \n"
            << (-d) << "\n";
  std::cout << "\n";
  std::cout << "123 == -(-123): \n"
            << std::boolalpha << (c == (-d)) << "\n";
  std::cout << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";

  std::cout << "Testing the overload of the += and + operators" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  bigint l("150");
  bigint m("150");
  bigint n("200");
  bigint q("90");
  bigint r("10");
  bigint s("250");
  bigint t("11");
  bigint v("15");

  std::cout << "l = 150, m = 150, l+=m: \n"
            << (l += m) << "\n";
  std::cout << "\n";
  std::cout << "l : \n"
            << (l) << "\n";
  std::cout << "\n";
  std::cout << "m : \n"
            << (m) << "\n";
  std::cout << "\n";

  std::cout << "n=200, s= 250, n + s: \n"
            << (n + s) << "\n";
  std::cout << "\n";
  std::cout << "n : \n"
            << (n) << "\n";
  std::cout << "\n";
  std::cout << "s : \n"
            << (s) << "\n";
  std::cout << "\n";
  std::cout << "Testing the consistency" << "\n";
  std::cout << "(150 + 90) + 11 == (90 + 11) + 150 : \n"
            << std::boolalpha << ((l + q) + t == (q + t) + l) << "\n";
  std::cout << "\n";
  std::cout << "Testing the consistency with random numbers (looped to check 10 times)" << "\n";
  for (size_t i = 0; i < 10; ++i)
  {
    const std::pair<int64_t, int64_t> indices_a = random_pair(-92233720368547758, 92233720368547758); //-92233720368547758, 92233720368547758
    const std::pair<int64_t, int64_t> indices_b = random_pair(-92233720368547758, 92233720368547758);
    int64_t a_ran = indices_a.first;
    int64_t b_ran = indices_a.second;
    int64_t c_ran = indices_b.first;
    int64_t d_ran = indices_b.second;
    std::cout << "\n";
    bigint a_big(a_ran);
    bigint b_big(b_ran);
    bigint c_big(c_ran);
    bigint d_big(d_ran);
    std::cout << "a : " << a_big << "\n";
    std::cout << "b : " << b_big << "\n";
    std::cout << "c : " << c_big << "\n";
    std::cout << "d : " << d_big << "\n";

    std::cout << "(a + b) + c == (b + c) + a : \n";
    std::cout << "(" << a_big << "+" << b_big << ") +" << c_big << " == (" << b_big << "+" << c_big << ") +" << a_big << ":\n";
    std::cout << std::boolalpha << (((a_big + b_big) + c_big) == ((b_big + c_big) + a_big)) << "\n";
    std::cout << "------------------------------------------------------" << "\n";
    std::cout << "\n";
  }
  std::cout << "Testing the overload of the -= and - operators" << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "l = 300, m = 150, l-=m: \n"
            << (l -= m) << "\n";
  std::cout << "\n";
  std::cout << "l : \n"
            << (l) << "\n";
  std::cout << "\n";
  std::cout << "m : \n"
            << (m) << "\n";
  std::cout << "\n";

  std::cout << "n=200, s= 250, n - s: \n"
            << (n - s) << "\n";
  std::cout << "\n";
  std::cout << "n : \n"
            << (n) << "\n";
  std::cout << "\n";
  std::cout << "s : \n"
            << (s) << "\n";
  std::cout << "\n";
  std::cout << "Testing the consistency" << "\n";
  std::cout << "(150 + 90) - 11 == 150 + (90 - 11) : \n"
            << std::boolalpha << ((l + q) - t == l + (q - t)) << "\n";
  std::cout << "\n";
  std::cout << "Testing the consistency with random numbers (looped to check 10 times)" << "\n";
  for (size_t i = 0; i < 10; ++i)
  {
    const std::pair<int64_t, int64_t> indices_a = random_pair(-92233720368547758, 92233720368547758); //-92233720368547758, 92233720368547758
    const std::pair<int64_t, int64_t> indices_b = random_pair(-92233720368547758, 92233720368547758);
    int64_t a_ran = indices_a.first;
    int64_t b_ran = indices_a.second;
    int64_t c_ran = indices_b.first;
    int64_t d_ran = indices_b.second;
    std::cout << "\n";
    bigint a_big(a_ran);
    bigint b_big(b_ran);
    bigint c_big(c_ran);
    bigint d_big(d_ran);
    std::cout << "a : " << a_big << "\n";
    std::cout << "b : " << b_big << "\n";
    std::cout << "c : " << c_big << "\n";
    std::cout << "d : " << d_big << "\n";

    std::cout << "(a + b) - c == a + (b - c) : \n";
    std::cout << "(" << a_big << "+" << b_big << ") -" << c_big << " == " << a_big << "+" << "(" << b_big << " - " << c_big << ") :\n";
    std::cout << std::boolalpha << (((a_big + b_big) - c_big) == (a_big + (b_big - c_big))) << "\n";
    std::cout << "------------------------------------------------------" << "\n";
    std::cout << "\n";
  }
  std::cout << "Testing the overload of the ++ and -- operators, both pre and post cases" << "\n";
  bigint alpha("10");
  std::cout << "a : 10" << "\n";
  std::cout << "++a :";
  std::cout << std::boolalpha << ++alpha << "\n";
  std::cout << "a :";
  std::cout << std::boolalpha << (alpha) << "\n";
  std::cout << "a++:";
  std::cout << std::boolalpha << alpha++ << "\n";
  std::cout << "a :";
  std::cout << std::boolalpha << alpha << "\n";
  std::cout << "\n";
  std::cout << "--a :";
  std::cout << std::boolalpha << (--alpha) << "\n";
  std::cout << "a :";
  std::cout << std::boolalpha << alpha << "\n";
  std::cout << "a-- :";
  std::cout << std::boolalpha << (alpha--) << "\n";
  std::cout << "a :";
  std::cout << std::boolalpha << alpha << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";

  std::cout << "Testing the overload of the *= and * operators" << "\n";
  bigint mult_a("5");
  bigint mult_b("5");
  bigint mult_c("0");
  bigint mult_d("10");

  std::cout << "a : " << mult_a << "\n";
  std::cout << "b : " << mult_b << "\n";
  std::cout << "c : " << mult_c << "\n";
  std::cout << "d : " << mult_d << "\n";
  std::cout << "\n";

  std::cout << "a*= b: \n" << (mult_a *= mult_b) << "\n";
  std::cout << "\n";

  std::cout << "a : \n" << (mult_a) << "\n";

  std::cout << "\n";

  std::cout << "b : \n" << (mult_b) << "\n";
  std::cout << "\n";

  std::cout << "b =  5, d= 10, n * s: \n" << (mult_b * mult_d) << "\n";
  std::cout << "\n";

  std::cout << "b * 0 : \n" << (mult_b * mult_c) << "\n";
  std::cout << "\n";
  std::cout << "Testing the consistency (commutativity of the product) with random numbers (looped to check 10 times)" << "\n";
  for (size_t i = 0; i < 10; ++i)
  {
    const std::pair<int64_t, int64_t> indices_a = random_pair(-92233720368547758, 92233720368547758); //-92233720368547758, 92233720368547758
    const std::pair<int64_t, int64_t> indices_b = random_pair(-92233720368547758, 92233720368547758);
    int64_t a_ran = indices_a.first;
    int64_t b_ran = indices_a.second;
    int64_t c_ran = indices_b.first;
    int64_t d_ran = indices_b.second;
    std::cout << "\n";
    bigint a_big(a_ran);
    bigint b_big(b_ran);
    bigint c_big(c_ran);
    bigint d_big(d_ran);
    std::cout << "a : " << a_big << "\n";
    std::cout << "b : " << b_big << "\n";
    std::cout << "c : " << c_big << "\n";
    std::cout << "d : " << d_big << "\n";

    std::cout << "(a * b) * c == a * (b * c) : \n";
    std::cout << "(" << a_big << "*" << b_big << ") *" << c_big << " == " << a_big << "*" << "(" << b_big << " * " << c_big << ") :\n";
    std::cout << std::boolalpha << (((a_big * b_big) * c_big) == (a_big * (b_big * c_big))) << "\n";
    std::cout << "------------------------------------------------------" << "\n";
    std::cout << "\n";
  }

  std::cout << "Testing the consistency (distributivity of the product) with random numbers (looped to check 10 times)" << "\n";
  for (size_t i = 0; i < 10; ++i)
  {
    const std::pair<int64_t, int64_t> indices_a = random_pair(-92233720368547758, 92233720368547758); //-92233720368547758, 92233720368547758
    const std::pair<int64_t, int64_t> indices_b = random_pair(-92233720368547758, 92233720368547758);
    int64_t a_ran = indices_a.first;
    int64_t b_ran = indices_a.second;
    int64_t c_ran = indices_b.first;
    int64_t d_ran = indices_b.second;
    std::cout << "\n";
    bigint a_big(a_ran);
    bigint b_big(b_ran);
    bigint c_big(c_ran);
    bigint d_big(d_ran);
    std::cout << "a : " << a_big << "\n";
    std::cout << "b : " << b_big << "\n";
    std::cout << "c : " << c_big << "\n";
    std::cout << "d : " << d_big << "\n";

    std::cout << "(a + b) * c == (a * c + b * c) : \n";
    std::cout << "(" << a_big << "+" << b_big << ") *" << c_big << " == (" << a_big << "*" << c_big << " + " << b_big << " * " << c_big << ") :\n";
    std::cout << std::boolalpha << (((a_big + b_big) * c_big) == (a_big * c_big + b_big * c_big)) << "\n";
    std::cout << "------------------------------------------------------" << "\n";
    std::cout << "\n";
  }
  std::cout << "Additionally, the exponentiation member function is tested" << "\n";
  std::cout << "a : " << mult_a << "\n";
  std::cout << "d : " << mult_d << "\n";
  std::cout << "a^d : " << mult_a.power(mult_d) << "\n";
  std::cout << "------------------------------------------------------" << "\n";

  std::cout << "\n";
  std::cout << "There random bigint generation is tested" << "\n";
  std::cout << "Generating a bigint with 5000 digits:";
  std::cout << random_bigint((size_t)5000) << "\n";

  bigint rand_a = random_bigint((size_t)100);
  bigint rand_b = random_bigint((size_t)100);
  bigint rand_c = random_bigint((size_t)100);
  std::cout << "\n";
  std::cout << "Testing the consistency (distributivity of the product) with random bigint numbers of 100 digits" << "\n";
  std::cout << "\n";
  std::cout << "a:" << rand_a;
  std::cout << "\n";
  std::cout << "b:" << rand_b;
  std::cout << "\n";
  std::cout << "c:" << rand_c;
  std::cout << "\n";
  std::cout << "(a * b) * c == a * (b * c) : ";
  //std::cout << "(" << rand_a << "*" << rand_b << ") *" << rand_c << " == " << rand_a << "*" << "(" << rand_b << " * " << rand_c << ") :\n";
  std::cout << std::boolalpha << (((rand_a * rand_b) * rand_c) == (rand_a * (rand_b * rand_c))) << "\n";
  std::cout << "------------------------------------------------------" << "\n";
  std::cout << "\n";
  std::cout << "Testing the results comparing with Python" << "\n";

  for (size_t i = 1; i <= 5; ++i)
  {
    std::string file = "bigint/data/data" + std::to_string(i) + ".txt";
    std::ifstream input(file);
    if (!input.is_open())
    {
      std::cout << "Error opening file!";
      return -1;
    }
    std::vector<std::string> lines;
    std::string line;
    while (getline(input, line))
      lines.push_back(line);

    bigint num1(lines[0]);
    bigint num2(lines[1]);
    bigint sum(lines[2]);
    bigint sub(lines[3]);
    bigint mult(lines[4]);

    std::cout << "\n";
    std::cout << "------------------------------------------------------" << "\n";
    std::cout << "Reading from the file: " << file << "\n";
    std::cout << "\n";
    std::cout << "Number 1 read: " << num1 << "\n";
    std::cout << "Number 2 read: " << num2 << "\n";
    std::cout << "Summation read from python: " << sum << "\n";
    std::cout << "Subtraction read from python: " << sub << "\n";
    std::cout << "Multiplication read from python: " << mult << "\n";
    std::cout << "\n";
    std::cout << "num1 + num2: ";
    std::cout << num1 + num2 << "\n";
    std::cout << "num1 + num2 == summation_python" << "\n";
    std::cout << std::boolalpha << (num1 + num2 == sum) << "\n";
    std::cout << "\n";
    std::cout << "num1 - num2 : ";
    std::cout << num1 - num2 << "\n";
    std::cout << "num1 - num2 == subtraction_python" << "\n";
    std::cout << std::boolalpha << (num1 - num2 == sub) << "\n";
    std::cout << "\n";
    std::cout << "num1 * num2 : ";
    std::cout << num1 * num2 << "\n";
    std::cout << "num1 * num2 == multiplication_python" << "\n";
    std::cout << std::boolalpha << (num1 * num2 == mult) << "\n";
    std::cout << "------------------------------------------------------" << "\n";
    input.close();
  }

  std::cout << "All done! :)" << "\n";
}