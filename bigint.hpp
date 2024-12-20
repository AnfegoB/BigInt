/**
 * @file bigint.hpp
 * @author Andres Gomez Bastidas (gomezbaa@mcmaster.ca)
 * @brief
 * @version 0.1
 * @date 2024-12-20
 * @copyright
 *
 */
#include <iostream>
#include <sstream>   //std::istringstream
#include <stdexcept> //std::invalid_argument
#include <string>    //std::string
#include <vector>    //std::vector
#include <random>

/**
 * @brief Obtain a random number in a specified range.
 *This function is taken and slightly modified from (https://github.com/bshoshany/thread-pool)
 * @tparam T The type of the values in the range.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return The random number.
 */
uint8_t random_n(uint8_t min, uint8_t max)
{
    static std::random_device rand_device;
    static std::mt19937_64 twister(rand_device());
    std::uniform_int_distribution<uint8_t> dist(min, max);
    return dist(twister);
}

/**
 * @brief
 * This bigint C++ class will allow to handle arbitrary-precision integers.
 * This class should be viewed as an extension of the usual C++ signed integer
 * types, except that your class will allow signed integers of unlimited range
 * limited only by the computer's memory. This specific implementation will
 * store internally the integers in vectors with base 10 digits[0]: sign
 * digits[1]: 10^0, digits[2]:10^1, and so forth.
 */
class bigint
{
    // Initializing the operator overloads, defining as friends allows to overload as non-member functions
    friend bigint operator-(bigint big);
    friend bigint &operator+=(bigint &lhs, bigint &rhs);
    friend bigint &operator-=(bigint &lhs, bigint &rhs);
    friend bigint &operator++(bigint &big);
    friend bigint operator++(bigint &big, int);
    friend bigint &operator--(bigint &big);
    friend bigint operator--(bigint &big, int);
    friend bigint operator+(bigint lhs, bigint rhs);
    friend bigint operator-(bigint lhs, bigint rhs);
    friend bigint &operator*=(bigint &lhs, const bigint &rhs);

    // The comparison operators do not need access to private members but are forward initialized to be able to use them in .power()
    friend bool operator==(const bigint &lhs, const bigint &rhs);
    friend bool operator>(const bigint &lhs, const bigint &rhs);
    friend bool operator<(const bigint &lhs, const bigint &rhs);
    friend bool operator>=(const bigint &lhs, const bigint &rhs);
    friend bool operator<=(const bigint &lhs, const bigint &rhs);

    friend bigint random_bigint(size_t const &num_digits);

public:
    //
    /**
     * @brief Default constructor creates the integer 0.
     */
    bigint()
    {
        digits = std::vector<uint8_t>{1, 0};
    }

    // Constructor 64-bit signed integer
    /**
     * @brief Construct a new bigint object from a int64_t integer
     * It takes the integer number as input. If it is zero creates the 0 bigint. If not, takes the magnitude
     * and starts taking the digits from right to left and storing them in a vector<int64_t>. Depending on the
     * sign the initial digit from the vector is selected 0: negative numbers, 1:positive numbers.
     * @param number_int64
     */
    bigint(int64_t &number_int64)
    {
        if (number_int64 == 0) // zero case
            digits = std::vector<uint8_t>{1, 0};
        else
        {
            digits = std::vector<uint8_t>(0);
            int64_t number_int64_magnitude = abs(number_int64);
            while (number_int64_magnitude > 0)
            {
                int64_t digit;
                digit = number_int64_magnitude % 10;
                digit = (uint8_t)digit;
                digits.insert(digits.begin(), (uint8_t)digit); // Stored in the same fashion as we read them
                number_int64_magnitude /= 10;                  // int division leaves the last digit out
            }
            if (number_int64 < 0)
                digits.insert(digits.begin(), 0);
            else
                digits.insert(digits.begin(), 1);
        }
    }

    // Constructor from string of digits
    /**
     * @brief Construct a new bigint object from a string of digits
     * The constructor catches cases in which the argument given is not a
     * number and throws an invalid argument error.
     * A positive number can either be defined with or without the + symbol.
     * A negative number requires the - symbol.
     * @param string_in
     */
    bigint(const std::string &string_in)
    {
        digits = std::vector<uint8_t>(0);
        if (string_in[0] == '-')
        {
            digits.insert(digits.begin(), 0);
            for (size_t l = 1; l < string_in.size(); ++l)
            {
                std::string s;
                std::string _str(1, string_in[l]);
                std::istringstream string_stream(_str);
                try
                {
                    while (getline(string_stream, s))
                        digits.push_back((uint8_t)stoi(s));
                }
                catch (const std::invalid_argument &e)
                {
                    throw std::invalid_argument("Expected a number!");
                }
            }
        }
        else if (string_in[0] == '+')
        {
            digits.insert(digits.begin(), 1);
            for (size_t l = 1; l < string_in.size(); ++l)
            {
                std::string s;
                std::string _str(1, string_in[l]);
                std::istringstream string_stream(_str);
                try
                {
                    while (getline(string_stream, s))
                        digits.push_back((uint8_t)stoi(s));
                }
                catch (const std::invalid_argument &e)
                {
                    throw std::invalid_argument("Expected a number!");
                }
            }
        }
        else
        {
            digits.insert(digits.begin(), 1);
            for (size_t m = 0; m < string_in.size(); ++m)
            {
                std::string s;
                std::string _str(1, string_in[m]);
                std::istringstream string_stream(_str);
                try
                {
                    while (getline(string_stream, s))
                        digits.push_back((uint8_t)stoi(s));
                }
                catch (const std::invalid_argument &e)
                {
                    throw std::invalid_argument("Expected a number!");
                }
            }
        }
    }
    /**
     * @brief Gets the vector object corresponding to the bigint digits
     * This is useful because then we can use the member functions of vector class when
     * overloading operators for the bigint class
     * @return std::vector<uint8_t>
     */
    std::vector<uint8_t> get_vec() const { return digits; }

    /**
     * @brief Exponentiation function, it gives the bigint number to the param big_b exponent.
     * This is a rough algorithm for exponentiation, it employs the multiplication overload and performs
     * the successive multiplications a^b --> a(a)(a)... b times
     * @param big_b
     * @return bigint
     */
    bigint power(bigint &big_b)
    {
        int64_t one = 1;
        bigint result(one);
        const bigint zero;
        bigint i;
        for (i = zero; i < big_b; i++)
        {
            result *= *this;
        }
        return result;
    }


    /**
     * @brief Internally the digits of the bigint are stored in a vector as 8-bit unsigned integers
     *
     */
private:
    std::vector<uint8_t> digits;
};

/**
 * @brief Overload of the << operator
 * Makes use of the array containing the bigint digits by
 * calling the get_vec() function.
 * @param out
 * @param big_integ
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &out, const bigint &big_integ)
{
    if (big_integ.get_vec()[0] == 0 && big_integ.get_vec().size() > 1) // First is 0: negative sign
    {
        out << "-";
        for (size_t i = 1; i < big_integ.get_vec().size(); ++i)
            out << (uint16_t)big_integ.get_vec()[i]; // Explicit typecasting to unint16_t to be able to print numerical values
    }
    else if (big_integ.get_vec()[0] == 1) // First is 1: positive sign
    {
        for (size_t i = 1; i < big_integ.get_vec().size(); ++i)
            out << (uint16_t)big_integ.get_vec()[i];
    }
    return out;
}

/**
 * @brief Overloading the == operator
 * This overload is slightly modified from the lecture notes in the case of vectors (section 5.2.3)
 * First the sizes between bigints are compared, as no two numbers with different number of digits can be equal.
 * Then every digit is compared, as the first refers to the sign, it also accounts for it.
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator==(const bigint &lhs, const bigint &rhs)
{
    if (lhs.get_vec().size() != rhs.get_vec().size())
        return false;
    for (size_t i = 0; i < lhs.get_vec().size(); ++i)
        if (lhs.get_vec()[i] != rhs.get_vec()[i])
            return false;
    return true;
}

/**
 * @brief Overloading the != operator
 * It is just the negation of the == case.
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator!=(const bigint &lhs, const bigint &rhs) { return !(lhs == rhs); }

/**
 * @brief Overloading the > operator
 * First the signs are checked, all positive numbers are greater than all negative ones.
 * Then the size of the left hand side is compared to siz of the right hand depending on the sign, and how close they are to 0.
 * If the digits have the same amount of digits then every digit must be checked, from the most significant to the least one.
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator>(const bigint &lhs, const bigint &rhs)
{
    if (lhs.get_vec()[0] == 1 &&
        rhs.get_vec()[0] == 0) // lhs is positive and rhs negative
        return true;
    if (lhs.get_vec()[0] == 0 &&
        rhs.get_vec()[0] == 1) // lhs is negative and rhs positive
        return false;

    if (lhs.get_vec()[0] == 0 && rhs.get_vec()[0] == 0) // both negative
    {
        if (lhs.get_vec().size() > rhs.get_vec().size()) // lhs is further from 0
            return false;

        if (lhs.get_vec().size() < rhs.get_vec().size()) // lhs is closer to 0
            return true;
        for (size_t i = 1; i < lhs.get_vec().size(); i++)  
                                                               // [0]
            if (lhs.get_vec()[i] > rhs.get_vec()[i])           // Checks between most significant, if its bigger is
                                                               // further
                return false;
            else if (lhs.get_vec()[i] < rhs.get_vec()[i]) // inverse condition
                return true;
        return false;
    }
    else // Same logic as before but for both positive numbers
    {
        if (lhs.get_vec().size() > rhs.get_vec().size())
            return true;

        if (lhs.get_vec().size() < rhs.get_vec().size())
            return false;

        for (size_t i = 1; i < lhs.get_vec().size(); i++)
            if (lhs.get_vec()[i] < rhs.get_vec()[i])
                return false;
            else if (lhs.get_vec()[i] > rhs.get_vec()[i])
                return true;
        return false;
    }
}

/**
 * @brief Overloading the >= operator
 * Having == and >, then => is constructed employing the logical or.
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator>=(const bigint &lhs, const bigint &rhs) { return ((lhs > rhs) || ((lhs == rhs))); }

/**
 * @brief Overloading the < operator
 * Checks for greater than or equal and negates the result.
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator<(const bigint &lhs, const bigint &rhs) { return !(lhs >= rhs); }

/**
 * @brief Overloading the <= operator
 * Cannot negate the = here too, it can only be included in one of the overloads.
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
bool operator<=(const bigint &lhs, const bigint &rhs) { return !(lhs > rhs); }

/**
 * @brief Overloading the - (unary) operator
 * The unary negation operator acting on bigint, changes the first element of
 * the array containing the digits. It is necessary to define the overload as a
 * friend function to be able to modify the private members of the class.
 *
 * @param big
 * @return bigint
 */
bigint operator-(bigint big)
{
    if (big.digits[0] == 0)
    {
        big.digits[0] = 1;
    }
    else
    {
        big.digits[0] = 0;
    }
    return big;
}

/**
 * @brief Overloading the += operator
 * Initially it checks for a trivial sum
 * It checks for sign operations (-a + b = b - a) and (a-b calls -= )
 * If both numbers have the same sign then it sums the magnitudes and keeps the sign. 
 * It takes the number at the least significant position and if the length is shorter than the result use a 0 instead
 * Then it is summed, if the result is bigger or equal than 10 then 1 is carried and the last digit is stored in result
 * @param lhs
 * @param rhs
 * @return bigint&
 */
bigint& operator+=(bigint &lhs, bigint &rhs)
{
    bigint zero;
    if (lhs == zero)
    {
        lhs = rhs;
        return lhs;
    }
    else if (rhs == zero)
    {
        return lhs;
    }
    if (lhs.get_vec()[0] == 0 && rhs.get_vec()[0] == 1)
    {
        bigint temp = -lhs;
        lhs = rhs;
        rhs = temp;
        return lhs -= rhs; 
    }
    else if (lhs.get_vec()[0] == 1 && rhs.get_vec()[0] == 0)
    {
        bigint temp2 = -rhs;
        return lhs -= temp2;
    }
    else
    {
        //
        const size_t max_size = std::max((lhs.get_vec().size()), (rhs.get_vec().size())); //+1 but the sign as first member takes it into consideration
        std::vector<uint8_t> result = std::vector<uint8_t>(0); // The maximum number of digits is the number of digits of the bigger number and a possible carry
        uint8_t carry = 0;
        uint8_t up;
        uint8_t dn;
        uint8_t sum;
        for (size_t i = 1; i <= (max_size); ++i) //Iterates from the first element (not sign) up to the maximum possible number of digits
        {
            // int m = -1 * (int)i;
            if (i < lhs.get_vec().size())
            {
                up = lhs.get_vec()[(lhs.get_vec().size() - i)];
            }
            else
            {
                up = 0;
            }
            if (i < rhs.get_vec().size())
            {
                dn = rhs.get_vec()[(rhs.get_vec().size() - i)];
            }
            else
            {
                dn = 0;
            }
            sum = up + dn + carry; // initially carry is 0, but for next iterations may be 1 
            if (sum >= 10) //If greater than 10 carry one over and keep the least significant digit
            {
                sum -= 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            result.push_back(sum);
        }
        std::reverse(result.begin(), result.end());
        if (result[0] == 0) // No need for the additional digit
        {
            result.erase(result.begin());
        }
        if (lhs.get_vec()[0] == 0 && rhs.get_vec()[0] == 0) //Adding the sign
        {
            result.insert(result.begin(), 0);
        }

        if (lhs.get_vec()[0] == 1 && rhs.get_vec()[0] == 1)
        {
            result.insert(result.begin(), 1);
        }



        lhs.digits = result; //Modifies lhs
        return lhs;
    }
}

/**
 * @brief Overloading the + operator
 * In this case the idea of overloading += first and then the + without reference is taken from the lecture notes.
 * @param lhs
 * @param rhs
 * @return bigint&
 */
bigint operator+(bigint lhs, bigint rhs)
{
    lhs += rhs;
    return lhs;
}

/**
 * @brief Overloading the pre-increment operator
 * It sums one and then returns the bigint
 * @param big
 * @return bigint&
 */
bigint &operator++(bigint &big)
{
    int64_t temp = 1;
    bigint temp_bigint(temp);
    big += temp_bigint;
    return big;
}

/**
 * @brief Overloading the post-increment operator
 * It returns the bigint and then increments by one, the dummy int parameter lets the compiler know it is the postfix case
 * @param big
 * @return bigint
 */
bigint operator++(bigint &big, int)
{
    bigint temp = big;
    int64_t temp_int = 1;
    bigint temp_bigint(temp_int);
    big += temp_bigint;
    return temp;
}

/**
 * @brief Overloading the -= operator
 * Initially it checks for a trivial sum
 * It checks for sign operations (a - (-b) = a + b) and (-a - ( - b ) = b - a)
 * It only receives positive bigint integers, it uses += to receive the appropriate input
 * It cheeks if the rhs is bigger than the lhs and decides if the sign will be -
 * It takes the number at the least significant position and if the length is shorter than the result use a 0 instead
 * Then it subtracts them and subtracts the carry, if the result is below 0 then 1 is carried over and 10 is summed.
 * @param lhs
 * @param rhs
 * @return bigint&
 */
bigint &operator-=(bigint &lhs, bigint &rhs)
{
    bigint zero;
    if (lhs == zero)
    {
        lhs = -rhs;
        return lhs;
    }
    else if (rhs == zero)
    {
        return lhs;
    }
    if (lhs.get_vec()[0] == 1 && rhs.get_vec()[0] == 0)
    {
        bigint temp = -rhs;
        return lhs += temp;
    }
    else if (lhs.get_vec()[0] == 0 && rhs.get_vec()[0] == 0)
    {
        bigint temp2 = -rhs;
        // -lhs;
        return lhs += temp2;
    }
    else if (lhs.get_vec()[0] == 0 && rhs.get_vec()[0] == 1)
    {
        bigint temp3 = -rhs;
        return lhs += temp3;
    }
    else
    {
        int sign_f = 0;
        if (rhs > lhs)
        {
            bigint temp4 = lhs;
            lhs = rhs;
            rhs = temp4;
            sign_f = 1;
        }
        const size_t max_size = std::max((lhs.get_vec().size()), (rhs.get_vec().size()));
        std::vector<uint8_t> result = std::vector<uint8_t>(0); // The maximum number of digits is the number of digits of the //
                // bigger number and a possible carry
        int16_t carry = 0; 
        int16_t up;
        int16_t dn;
        int16_t sub; // int types needed due to the possibility of negative values
        for (size_t i = 1; i <= (max_size); ++i)
        {
            // int m = -1 * (int)i;
            if (i >= lhs.get_vec().size() && i >= rhs.get_vec().size())
            { 
                continue;
            }
            if (i < lhs.get_vec().size())
            {
                up = (int16_t)lhs.get_vec()[(lhs.get_vec().size() - i)];
            }
                else
                {
                    up = 0;
                }
            if (i < rhs.get_vec().size())
            {
                dn = (int16_t)rhs.get_vec()[(rhs.get_vec().size() - i)];
            }
            else
            {
                dn = 0;
            }
            sub = up - dn - carry; // initially carry is 0, but for next iterations may
                                   // be 1 
            if (sub < 0)
            {
                sub += 10;
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            int16_t digit;
            digit = sub;
            digit = (uint8_t)digit;
            result.push_back( (uint8_t)digit);
        }
        std::reverse(result.begin(), result.end());
        if (result[0] == 0) // No need for the additional digit
        {
            result.erase(result.begin());
        }

        if (sign_f == 1)
        {
            result.insert(result.begin(), 0);
        }
        else if (sign_f == 0)
        {
            result.insert(result.begin(), 1);
        }
        if (result[1] == 0) // No need for the additional digit
        {
            result.erase(result.begin() + 1);
        }
        lhs.digits = result;
        return lhs;
    }
}

/**
 * @brief  Overloading the - operator
 * In this case the idea of overloading -= first and then the + without reference is taken from the lecture notes.
 * @param lhs
 * @param rhs
 * @return bigint
 */
bigint operator-(bigint lhs, bigint rhs)
{
    lhs -= rhs;
    return lhs;
}

/**
 * @brief Overloading the pre-decrement operator --
 * It decrements by one and then returns the bigint.
 * @param big
 * @return bigint&
 */
bigint& operator--(bigint& big)
{
    int64_t temp = 1;
    bigint temp_bigint(temp);
    big -= temp_bigint;
    return big;
}

/**
 * @brief Overloading the pre-decrement operator --
 * It returns the bigint and then decrements by one.
 * @param big
 * @return bigint
 */
bigint operator--(bigint& big , int)
{
    bigint temp = big;
    int64_t temp_int = 1;
    bigint temp_bigint(temp_int);
    big -= temp_bigint;
    return temp;
}

/**
 * @brief Overloading the *= operator
 * Initially it checks for a trivial product
 * It checks for sign operations (-- = +) (-+ = -)
 * It takes the digit from the lhs at the least significant position and iterates multiplying over all the digits of the rhs
 * After each multiplication it sums the carry and checks if the product is bigger than 10. 
 * If that is the case, takes the integer division as carry (most significant number) and the modulo as the resulting digit
 * This result is the first row, the next iteration is done employing the following significant digit (from right to left)
 * from the lhs, in this case the same multiplication process is performed, and so forth for all the digits in lhs.
 * After doing this, each row result is multiplied by 10^n where n is the row number, and then all of them are summed obtaining
 * the final product. 
 * @param lhs
 * @param rhs
 * @return bigint&
 */
bigint &operator*=(bigint &lhs, const bigint &rhs)
{
    bigint zero;
    if (lhs == zero or rhs == zero)
    {
        lhs = zero;
        return lhs;
    }
    uint8_t sign = 1;
    if (lhs.get_vec()[0] == 0 && rhs.get_vec()[0] == 1)
    {
        sign = 0;
    }
    else if (lhs.get_vec()[0] == 1 && rhs.get_vec()[0] == 0)
    {
        sign = 0;
    }
    else if (lhs.get_vec()[0] == rhs.get_vec()[0])
    {
        sign = 1;
    }
    int16_t carry = 0;
    bigint prev;
    bigint current;
    int16_t product;
    for (int16_t i = (int16_t)lhs.get_vec().size() - 1; i >= 0; i--)
    {
        std::vector<uint8_t> result = std::vector<uint8_t>(0);
        int16_t row = (int16_t)lhs.get_vec().size() - i - 1;
        for (int16_t j = (int16_t)rhs.get_vec().size() - 1; j >= 0; j--)
        {

            if (i == 0 and j == 0)
            {
                continue;
            }
            else if (i == 0 or j == 0)
            {
                product = 0;
            }
            else
            {
                product = lhs.get_vec()[(size_t)i] * rhs.get_vec()[(size_t)j];
            }

            product += carry;
            if (product >= 10)
            {
                carry = product / 10;
                product = product % 10;
            }
            else
            {
                carry = 0;
            }
            if (product >= 10)
            {
                int16_t digit1;
                digit1 = product % 10;
                digit1 = (uint8_t)digit1;

                int16_t digit2;
                digit2 = product / 10;
                digit2 = (uint8_t)digit2;

                result.insert(result.begin(), (uint8_t)digit1);
                result.insert(result.begin(), (uint8_t)digit2);
            }
            else
            {
                int16_t digit;
                digit = product;
                digit = (uint8_t)digit;
                result.insert(result.begin(), (uint8_t)product);
            }
        }

        if (result[0] == 0)
        {
            result.erase(result.begin());
        }
        result.insert(result.begin(), 1);
        for (int64_t k = 0; k < row; ++k)
        {
            result.push_back(0);
        }
        current.digits = result;
        current += prev;
        prev = current;
    }
    current.digits[0] = sign;
    lhs = current;
    return lhs;
}

/**
 * @brief Overloading the * operator
 * In this case the idea of overloading *= first and then the * without reference is taken from the lecture notes.
 * @param lhs
 * @param rhs
 * @return bigint
 */
bigint operator*(bigint lhs, const bigint &rhs)
{
    lhs *= rhs;
    return lhs;
}


/**
 * @brief Generates a random bigint number from a given number of digits
 * 
 * @param num_digits 
 * @return bigint 
 */
bigint random_bigint(size_t const &num_digits)
{
    std::vector<uint8_t> digits_r = std::vector<uint8_t>(0);
    bigint temp;
    uint8_t sign = random_n(0, 1);
    for (size_t i = 0; i < num_digits; i++)
    {
        uint8_t indices_a = random_n(0, 9);
        digits_r.insert(digits_r.begin(), indices_a);
        // std::cout << indices_a << "\n";
    }
    digits_r.insert(digits_r.begin(), sign);
    temp.digits = digits_r;
    return temp;
}