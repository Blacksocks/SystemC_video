#include <iostream>

// Calculate greatest common divisor between x and y
int pgcd(unsigned int x, unsigned int y)
{
    int min = (x < y) ? x : y;
    int max = (x < y) ? y : x;
    if(max == min)
        return min;
    return pgcd(min, max - min);
}

int main(int argc, char * argv[])
{
    std::cout << "pgcd(36,60): " << pgcd(36, 60) << std::endl;
    std::cout << "pgcd(42,63): " << pgcd(42, 63) << std::endl;
    std::cout << "pgcd(357,561): " << pgcd(357, 561) << std::endl;
    return 0;
}
