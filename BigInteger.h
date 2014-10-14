#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <vector>
#include <iostream>
#include <string>
#include "BigInteger.h"

class BigInteger
{


public:

std::vector<int> a;
    bool sign;

friend int compare (BigInteger ab,BigInteger bb);
    BigInteger ();
    BigInteger (int);
    BigInteger(BigInteger const& right);
    BigInteger (std::string const& st);
    friend std::string toString (BigInteger right);
    BigInteger& operator+=(BigInteger const& right);
    BigInteger& operator=(BigInteger const& right);
    BigInteger& operator-=(BigInteger const& right);
    BigInteger& operator*=(BigInteger const& right);
    BigInteger& operator*(BigInteger const& right);

private:


};

BigInteger operator+(BigInteger left,BigInteger const& right);
BigInteger operator-(BigInteger left,BigInteger const& right);
std::ostream& operator<<(std::ostream& so, const BigInteger& consst);
std::istream& operator>>(std::istream& so, BigInteger& consst);
std::string to_string (int);
int get_amz (int);
#endif
