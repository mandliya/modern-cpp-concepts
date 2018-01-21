#include <iostream>

int main()
{
    const int x = 4;
    const int y = 4;

    // This will not fail as condition is true.
    static_assert(x == y, "The x is not equal to y");

    // This will generate error
    static_assert(x > y, "x should be greater than y");

    // This will not compile in C++11 but will compile in C++17.
    static_assert(x < y);

    return 0;
}