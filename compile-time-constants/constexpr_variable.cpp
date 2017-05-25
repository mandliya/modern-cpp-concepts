/**
 *  Concept 4 : compile time constants.
 */

#include <iostream>

int main()
{
  constexpr uint32_t MEMORY_SIZE{ 512 };
  std::cout << MEMORY_SIZE << std::endl;
}
