#include "BigInteger.h"
#include <iostream>
int main()
{

    BigInteger b,c;
    std::cin>>c>>b;

    b = (b = b - c) + c;

    std::cout << b ;
    return 0;
}
